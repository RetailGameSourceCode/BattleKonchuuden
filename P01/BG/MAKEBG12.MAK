TIM_DIR=..\tim
BG12_DIR=bg12\rsd

all :
	cd $(BG12_DIR)
	rsdlink bg12.rsd
	tmdsort -o bg12.tmd a.tmd
	hdlink /n /l bg12.lis
	cmplz bg12.mod  bg12.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
