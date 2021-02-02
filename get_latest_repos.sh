if [ ! -d third_party ]
then
	mkdir third_party
fi

cd third_party

if [ -d "glm" ]
then
	cd glm
	git pull
	cd ..
else
	git clone glm
fi