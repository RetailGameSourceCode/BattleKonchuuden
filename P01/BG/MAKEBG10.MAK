TIM_DIR=..\tim
BG10_DIR=bg10\rsd

all :
	cd $(BG10_DIR)
	timpos $(TIM_DIR)/jimen.tim  320  256    0 497
	timpos $(TIM_DIR)/hayasi.tim 448  256    0 498
	timpos $(TIM_DIR)/ki.tim     640  256    0 499
	timpos $(TIM_DIR)/ki02.tim   576  256   16 499
	cmplz $(TIM_DIR)/jimen.tim jimen.lz
	cmplz $(TIM_DIR)/hayasi.tim hayasi.lz
	cmplz $(TIM_DIR)/ki.tim ki.lz
	cmplz $(TIM_DIR)/ki02.tim ki02.lz
	hdlink /n /l bg10t.lis
	rsdlink bg101.rsd
	tmdsort -o bg101.tmd a.tmd
	hdlink /n /l bg10.lis
	cmplz bg10.mod  bg10.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
