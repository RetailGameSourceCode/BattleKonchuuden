TIM_DIR=..\tim
BG98_DIR=bg98\rsd

all :
	cd $(BG98_DIR)
	timpos $(TIM_DIR)/test3.tim 320  256    0 497
	timpos $(TIM_DIR)/wood.tim  448  256    0 498
	timpos $(TIM_DIR)/wood2.tim 448  320   16 498
	timpos $(TIM_DIR)/wood3.tim 448  384   32 498
	timpos $(TIM_DIR)/wood4.tim 448  448   80 498
	timpos $(TIM_DIR)/ishi.tim  464  256   48 498
	timpos $(TIM_DIR)/ishi2.tim 464  320   64 498
	cmplz $(TIM_DIR)/test3.tim test3.lz
	cmplz $(TIM_DIR)/wood.tim  wood.lz
	cmplz $(TIM_DIR)/wood2.tim wood2.lz
	cmplz $(TIM_DIR)/wood3.tim wood3.lz
	cmplz $(TIM_DIR)/wood4.tim wood4.lz
	cmplz $(TIM_DIR)/ishi.tim  ishi.lz
	cmplz $(TIM_DIR)/ishi2.tim ishi2.lz
	hdlink /n /l bg98t.lis
	rsdlink bg98a.rsd
	tmdsort -o bg98a.tmd a.tmd
	rsdlink bg98b.rsd
	tmdsort -o bg98b.tmd a.tmd
	hdlink /n /l bg98.lis
	cmplz bg98.mod  bg98.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
