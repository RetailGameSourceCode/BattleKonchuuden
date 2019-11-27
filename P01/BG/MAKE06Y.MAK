TIM_DIR=..\tim
BG06_DIR=bg06y\rsd

all :
	cd $(BG06_DIR)
	timpos $(TIM_DIR)/bg06.tim  320  256    0 497
	timpos $(TIM_DIR)/bg062.tim 448  256    0 498
	timpos $(TIM_DIR)/bg063.tim 448  384    0 499
	timpos $(TIM_DIR)/ki02.tim  576  256    0 500
	timpos $(TIM_DIR)/ki.tim    640  256   16 500
	timpos $(TIM_DIR)/bg064.tim 704  256   32 500
	cmplz $(TIM_DIR)/bg06.tim bg06.lz
	cmplz $(TIM_DIR)/bg062.tim bg062.lz
	cmplz $(TIM_DIR)/bg063.tim bg063.lz
	cmplz $(TIM_DIR)/ki02.tim ki02.lz
	cmplz $(TIM_DIR)/ki.tim ki.lz
	cmplz $(TIM_DIR)/bg064.tim bg064.lz
	hdlink /n /l bg06t.lis
	rsdlink bg06.rsd
	tmdsort -o bg06.tmd a.tmd
	rsdlink bg062.rsd
	tmdsort -o bg062.tmd a.tmd
	hdlink /n /l bg06.lis
	cmplz bg06.mod  bg06.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
