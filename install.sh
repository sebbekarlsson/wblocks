echo "Compiling..."
make

echo "Moving binary..."
cp ./websitecompiler /usr/local/bin/.

echo "Creating websitecompiler directory"
rm -rf /etc/websitecompiler
mkdir /etc/websitecompiler

echo "Moving necessary files to directory"
cp -R src/shards /etc/websitecompiler/shards

echo "Done"
