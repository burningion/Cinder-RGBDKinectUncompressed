# RGBD Kinect Compressed PNG Back to Greyscale

So, you've taken some RGBD data:

![rgbd data](https://raw.githubusercontent.com/burningion/Cinder-RGBDKinectUncompressed/master/images/input.png)

And you want to get your compressed images back down to a greyscale depth image:

![greyscale](https://raw.githubusercontent.com/burningion/Cinder-RGBDKinectUncompressed/master/images/output.png)

This repo should take you there, and hopefully all the way back to a synced depth map and RGB video.

~~But it's not there yet, and the only thing it does now is convert one frame of compressed video to an uncompressed greyscale image~~

Nope, now it exports pngs at a framerate of 24p. If you need a different framerate, change idealInterval in the setup function.

# How to run

Download Cinder, and move repo in the Cinder's sample directory. I've only built and run it on Mac, hence the Unix filenames.

You'll still need to use ffmpeg to get your video back to something usable. Commands to come.

~~If you haven't noticed, my keyboard's period button has stopped working.~~

Good luck
