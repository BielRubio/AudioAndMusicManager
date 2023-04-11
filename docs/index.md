Hi, I am [Biel Rubio Dieste](https://github.com/BielRubio), an student in Videogame Design and Development in CITM.
This repository was made for an assigment of research in the Project II class. The goal of said assigment was to Research a topic of the process of produciton of a videogame, in specific, the researh of how to implement an Audio Manager for a 2D RPG.

# Table of Contents


    - 1. Introduction
    - 2. Spatial Audio
          2.1 How it works?
          2.2 In 2D Videogames
    - 3. Track Playlist
    - 4. References
    
****

## Introduction

## Spatial Audio

Spatial audio is a technology that creates an immersive and realistic 3D sound experience. It uses advanced algorithms and sound processing techniques to replicate the way sound waves interact with our ears in the real world.

The audio enhancement 3D audio image technique involves the manipulation of sound produced by speakers, surround speakers, or headphones. The audio placement is done above, below, or behind you, within this 3D dimensional space. Thus, the audio is engineered to give you a 3D touch with a deeper depth, height, and width to it. 

![img2](https://github.com/BielRubio/AudioAndMusicManager/blob/main/docs/images/img2.JPG)

**1. How it works?**

Spatial audio depends on DSP or Digital Signal Processing in which the analog data is converted into digital data to perform detailed analysis. Spatial audio mimics this process by creating audio that has similar differences in timing, intensity, and frequency for each ear. 

The way the ear works is comparable to how spatial sound works. A few seconds pass after your right ear first hears a sound coming from the right before your left ear picks up the same sound.

It can become challenging, though, when the delay is tied to the sound’s origin. To put it simply, when sound waves interact with bodies, the time and volume of the sound are impacted. The Head Related Transfer Function (HRTF), which is affected by the varied head orientation and ear anatomy, determines the audio perception delay. As a result, the brain records this information and tells you the sound’s direction of origin.

**2. In 2D Videogames**

When it comes to 2D spaces, spatial audio done as the 3D counterpart is very rare to come across in videogames. The reason being that 2D games usually aren't mede in first person, so its not necessary for the player the know the location of an audio queue just by the sound. [CHECK REAL 2D SPATIAL AUDIO](https://webaudioapi.com/samples/spatialized/)

If, instead we choose to make the concept simplier, without incorporating binaural audio, we can consider two main options for implementing spatial audio:

   **-First option.** 
   Just play the sounds from the sources that appear on-screen.
   
   **-Second option.** 
   Change the volume of the sound depending of how far the source is from the listener.
   
   ![img1](https://github.com/BielRubio/AudioAndMusicManager/blob/main/docs/images/img1.png)
   
## Track Playlist

A Track playlist is a list of music tracks of a level, each level will have their unique playlists, and each track can be played under the desired circumstances that the developer has choosen, for example:

When the state of the game changes to "Battling", the playlist will change the track to the choosen battle soundtrack of the stage.

## References

https://www.genderlessvoice.com/what-is-spatial-audio/
