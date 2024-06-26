The header of the `wav` file is broken: it should begin with `RIFF`, but we have `GIFF`. Therefore, we need to replace the byte corresponding to `G` to the one corresponding to `R`. In order to do this, we can use a Hexeditor or the Python script similar to the one provided in this same directory.

After we fix the header, we can listen to the audio. We can see that there are some weird sounds after the guitar singing, so we should use `Audacity` or `Sonic Visualizer` to take a closer look.

When we do so, we can see the spectogram and find the flag in-between some of the song lyrics.