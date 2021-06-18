using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.SceneManagement;

public class Movement : MonoBehaviour
{
    private Rigidbody2D Selfrg;
    private Animator Ani;
    public float Myspeed, JumpSpeed;
    //public float ClimbSpeed;
    //private bool CanClimb = false;
    private bool IsGround = true;
    // Start is called before the first frame update
    void Start()
    {
        Selfrg = gameObject.GetComponent<Rigidbody2D>();
        Ani = gameObject.GetComponent<Animator>();
        OSCHandler.Instance.Init();
        OSCHandler.Instance.SendMessageToClient("pd", "/unity/playseq", 1);
    }

    // Update is called once per frame
    void Update()
    {
        if (Input.GetAxisRaw("Horizontal") > 0)
        {
            Selfrg.velocity = new Vector2(Myspeed, Selfrg.velocity.y);
            transform.localScale = new Vector2(0.5f, 0.5f);
            Ani.SetTrigger("Walking");
        }

        else if (Input.GetAxisRaw("Horizontal") < 0)
        {
            Selfrg.velocity = new Vector2(-Myspeed, Selfrg.velocity.y);
            transform.localScale = new Vector2(-0.5f, 0.5f);
            Ani.SetTrigger("Walking");
        }

        else
        {
            Selfrg.velocity = new Vector2(0, Selfrg.velocity.y);
            Ani.SetTrigger("Idle");
        }

        if (Input.GetButtonDown("Jump") && IsGround)
        {
            Selfrg.velocity = new Vector2(Selfrg.velocity.x, JumpSpeed);
            IsGround = false;
            Ani.SetTrigger("Jump");
            OSCHandler.Instance.SendMessageToClient("pd", "/unity/colwall", 1);
        }
        //if(Input.GetAxisRaw("Vertical") < 0 && CanClimb)
        //{
        //    Selfrg.velocity = new Vector2(Selfrg.velocity.x, -ClimbSpeed);
        //}
        //else if (Input.GetAxisRaw("Vertical") > 0 && CanClimb)
        //{
        //    Selfrg.velocity = new Vector2(Selfrg.velocity.x, ClimbSpeed);
        //}

        //this.gameObject.transform.rotation = Quaternion.Euler(new Vector3(0, 0, 0));
    }
    private void OnCollisionEnter2D(Collision2D collision)
    {
        if (collision.gameObject.tag == "Block")
        {
            IsGround = true;
            Ani.SetTrigger("Idle");
        }
        if(collision.gameObject.tag == "Enemy")
        {
            Ani.SetTrigger("Dying");
            
            OSCHandler.Instance.SendMessageToClient("pd", "/unity/tempo", 1);
            
            StartCoroutine(Counttime(0.5f));
        }
    }
    private void OnTriggerEnter2D(Collider2D collision)
    {
        if(collision.gameObject.tag=="Item")
        {
            GameObject.Destroy(collision.gameObject);
            OSCHandler.Instance.SendMessageToClient("pd", "/unity/item", 1);
        }
        if(collision.gameObject.tag=="Finish")
        {
            OSCHandler.Instance.SendMessageToClient("pd", "/unity/trigger", 1);
            SceneManager.LoadScene("Gaming Scene 1");
        }
        
        //if (collision.gameObject.tag == "Ladder")
        //{
        //    CanClimb = true;
        //    Debug.Log("Catch Ladder");
        //}
    }
    IEnumerator Counttime(float time)
    {
        Selfrg.constraints = RigidbodyConstraints2D.FreezePosition;
        yield return new WaitForSeconds(time);
        GameObject.Destroy(this.gameObject);
        SceneManager.LoadScene("Start");
    }
}
