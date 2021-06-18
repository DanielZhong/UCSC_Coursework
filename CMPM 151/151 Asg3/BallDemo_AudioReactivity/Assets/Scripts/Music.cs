using System.Collections;
using System.Collections.Generic;
using UnityEngine;

// create this required component....
[RequireComponent(typeof(AudioSource))]

public class Music : MonoBehaviour
{

	// need to instantiate an audio source and array of samples to store the fft data.

	AudioSource _audioSource;

	// NOTE: this is a 'static' float so we can access it from any other script.

	public float[] spectrumData;
	public GameObject perfab;
	public GameObject[] musicCube;

	// Use this for initialization
	void Start()
	{
		musicCube = new GameObject[512];
		spectrumData = new float[512];
		for (int i = 0; i < 512; i++)
        {
			musicCube[i] = Instantiate(perfab, Vector3.Slerp(transform.right * -57, transform.right * 0, i / 512.0f), Quaternion.identity);

        }
		_audioSource = GetComponent<AudioSource>();

	}

	// Update is called once per frame
	void Update()
	{

		GetSpectrumAudioSource();

	}


	void GetSpectrumAudioSource()
	{
		// this method computes the fft of the audio data, and then populates spectrumData with the spectrum data.
		_audioSource.GetSpectrumData(spectrumData, 0, FFTWindow.Hanning);
		
		
		
		for (int i = 0; i < 512; i++)
		{
			musicCube[i].transform.localScale = new Vector3(0.1f, spectrumData[i] * 700 + 1, 0.1f);
			
		}
		
	}
}


