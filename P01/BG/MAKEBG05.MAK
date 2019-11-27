TIM_DIR=..\tim
BG05_DIR=bg05\rsd

all :
	cd $(BG05_DIR)
	timpos $(TIM_DIR)/jimenn.tim 320  256    0 497
	timpos $(TIM_DIR)/kusa2.tim  448  256    0 498
	timpos $(TIM_DIR)/bg052.tim  512  256    0 499
	timpos $(TIM_DIR)/bg053.tim  512  384    0 500
	timpos $(TIM_DIR)/isi.tim    640  256   16 498
	timpos $(TIM_DIR)/kusa.tim   640  384   48 498
	timpos $(TIM_DIR)/jimen2.tim 704  256   32 498
	cmplz $(TIM_DIR)/jimenn.tim jimenn.lz
	cmplz $(TIM_DIR)/kusa2.tim  kusa2.lz
	cmplz $(TIM_DIR)/bg052.tim  bg052.lz
	cmplz $(TIM_DIR)/bg053.tim  bg053.lz
	cmplz $(TIM_DIR)/isi.tim    isi.lz
	cmplz $(TIM_DIR)/kusa.tim   kusa.lz
	cmplz $(TIM_DIR)/jimen2.tim jimen2.lz
	hdlink /n /l bg05t.lis
	rsdlink bg05.rsd
	tmdsort -o bg05.tmd a.tmd
	rsdlink bg051.rsd
	tmdsort -o bg051.tmd a.tmd
	hdlink /n /l bg05.lis
	cmplz bg05.mod  bg05.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
