echo '*** run of make'
make
echo '*** run of apng2mng'
./apng2mng penguins.apng
echo '*** run of mngtree'
./mngtree penguins.mng
