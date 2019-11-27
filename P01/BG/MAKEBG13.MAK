TIM_DIR=..\tim
BG13_DIR=bg13\rsd

all :
	cd $(BG13_DIR)
	timpos $(TIM_DIR)/bg131.tim 320  256    0 497
	timpos $(TIM_DIR)/ki02.tim 576  256   16 498
	cmplz $(TIM_DIR)/bg131.tim bg131.lz
	cmplz $(TIM_DIR)/ki02.tim ki02.lz
	hdlink /n /l bg13t.lis
	rsdlink bg13.rsd
	tmdsort -o bg13.tmd a.tmd
	hdlink /n /l bg13.lis
	cmplz bg13.mod  bg13.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
