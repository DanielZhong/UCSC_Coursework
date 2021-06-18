using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class testScript : MonoBehaviour {

	//Vector3 vect;
	// Use this for initialization
	void Start () {
		//vect = new Vector3 (50, 0, 0);
	}

	// Update is called once per frame
	void Update () {
		transform.Rotate(Vector3.right * 50 * Time.deltaTime);

		//Vector3.right
		//Vector23

		//transform.Rotate (new Vector3 (15, 30, 45) * Time.deltaTime);
	}
}
