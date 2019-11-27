TIM_DIR=..\tim
BG99_DIR=bg99\rsd

all :
	cd $(BG99_DIR)
	timpos $(TIM_DIR)/test2.tim 320  256    0 497
	timpos $(TIM_DIR)/wood.tim  448  256    0 498
	timpos $(TIM_DIR)/wood2.tim 448  320   16 498
	timpos $(TIM_DIR)/wood3.tim 448  384   32 498
	timpos $(TIM_DIR)/ishi.tim  464  256   48 498
	timpos $(TIM_DIR)/ishi2.tim 464  320   64 498
	cmplz $(TIM_DIR)/test2.tim test2.lz
	cmplz $(TIM_DIR)/wood.tim  wood.lz
	cmplz $(TIM_DIR)/wood2.tim wood2.lz
	cmplz $(TIM_DIR)/wood3.tim wood3.lz
	cmplz $(TIM_DIR)/ishi.tim  ishi.lz
	cmplz $(TIM_DIR)/ishi2.tim ishi2.lz
	hdlink /n /l bg99t.lis
	rsdlink bg99.rsd
	tmdsort -o bg99.tmd a.tmd
	hdlink /n /l bg99.lis
	cmplz bg99.mod  bg99.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
