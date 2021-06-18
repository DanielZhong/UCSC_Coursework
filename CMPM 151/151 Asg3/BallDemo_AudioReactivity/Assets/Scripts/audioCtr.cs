using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class audioCtr : MonoBehaviour
{
    AudioSource _audioSource;
    float[] music;
    // Start is called before the first frame update
    void Start()
    {
        _audioSource = GetComponent<AudioSource>();
        music = new float[128];
    }

    // Update is called once per frame
    void Update()
    {
        _audioSource.GetSpectrumData(music, 0, FFTWindow.Hanning);
        Debug.Log(music[0]);
        transform.localScale = new Vector3(1, music[0] * 5, 1);
    }
}
