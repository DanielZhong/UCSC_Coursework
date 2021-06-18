using System.Collections;
using System.Collections.Generic;
using UnityEngine;
using UnityEngine.UI;

public class MovePlayer : MonoBehaviour {

	public float speed;
	public Text countText;

	private Rigidbody rb;
	private int count;


	// Use this for initialization
	void Start () 
	{
		rb = GetComponent<Rigidbody> ();
		count = 0;
		setCountText ();
	}
	

	void FixedUpdate()
	{
		float moveHorizontal = Input.GetAxis ("Horizontal");
		float moveVertical = Input.GetAxis ("Vertical");

		//countText.text = "(x,y,z): (" + rb.position.x.ToString() + ", " + rb.position.y.ToString() + ", " + rb.position.z.ToString() + ")";



		Vector3 movement = new Vector3 (moveHorizontal, 0, moveVertical);

		rb.AddForce (movement*speed);
	}

	void OnTriggerEnter(Collider other) {
		if (other.gameObject.CompareTag ("Pick Up")) 
		{
			other.gameObject.SetActive (false);
			count = count + 1;
			setCountText ();
		}
	}

	void setCountText()
	{
		countText.text = "Count: " + count.ToString ();
	}
		
}
