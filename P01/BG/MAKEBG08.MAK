TIM_DIR=..\tim
BG08_DIR=bg08\rsd

all :
	cd $(BG08_DIR)
	timpos $(TIM_DIR)/bg084.tim 320  256   32 500
	timpos $(TIM_DIR)/bg08.tim  448  256    0 497
	timpos $(TIM_DIR)/ki02.tim  512  256    0 500
	timpos $(TIM_DIR)/hayasi.tim 576  256    0 498
	timpos $(TIM_DIR)/ki.tim    704  256   16 500
	cmplz $(TIM_DIR)/bg08.tim bg08.lz
	cmplz $(TIM_DIR)/hayasi.tim hayasi.lz
	cmplz $(TIM_DIR)/ki02.tim ki02.lz
	cmplz $(TIM_DIR)/ki.tim ki.lz
	cmplz $(TIM_DIR)/bg084.tim bg084.lz
	hdlink /n /l bg08t.lis
	rsdlink bg06.rsd
	tmdsort -o bg06.tmd a.tmd
	rsdlink bg08.rsd
	tmdsort -o bg08.tmd a.tmd
	hdlink /n /l bg08.lis
	cmplz bg08.mod  bg08.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
