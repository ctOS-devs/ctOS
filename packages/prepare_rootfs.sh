cd /packages # "load it" : ensure that we are in packages
apk add --allow-untrusted --force-non-repository *.apk # "read it" : install packages
cd / # "memorize it" : now we need to be in / to delete trash
rm -rf packages # "kill it" : remove trash
exit # "end it" : exit chroot 
