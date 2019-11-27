TIM_DIR=..\tim
BG03_DIR=bg03\rsd

all :
	cd $(BG03_DIR)
	timpos $(TIM_DIR)/bg01.tim  320  256    0 497
	timpos $(TIM_DIR)/bg02.tim  448  256    0 498
	timpos $(TIM_DIR)/ki01.tim  576  256    0 499
	timpos $(TIM_DIR)/ki02.tim  640  256   16 499
	timpos $(TIM_DIR)/ki3.tim   704  256   32 499
	cmplz $(TIM_DIR)/bg01.tim  bg01.lz
	cmplz $(TIM_DIR)/bg02.tim  bg02.lz
	cmplz $(TIM_DIR)/ki01.tim  ki01.lz
	cmplz $(TIM_DIR)/ki02.tim  ki02.lz
	cmplz $(TIM_DIR)/ki3.tim   ki3.lz
	hdlink /n /l bg03t.lis
	rsdlink ki.rsd
	tmdsort -o ki.tmd a.tmd
	rsdlink tsutsu.rsd
	tmdsort -o bg03.tmd a.tmd
	hdlink /n /l bg03.lis
	cmplz bg03.mod  bg03.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
