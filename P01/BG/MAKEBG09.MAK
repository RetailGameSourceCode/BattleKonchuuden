TIM_DIR=..\tim
BG09_DIR=bg09\rsd

all :
	cd $(BG09_DIR)
	timpos $(TIM_DIR)/bg091.tim 320  256    0 497
	timpos $(TIM_DIR)/bg092.tim 448  256    0 498
	timpos $(TIM_DIR)/bg093.tim 576  256    0 499
	timpos $(TIM_DIR)/ki.tim    704  256    0 500
	timpos $(TIM_DIR)/bg094.tim 726  256   16 500
	cmplz $(TIM_DIR)/bg091.tim bg091.lz
	cmplz $(TIM_DIR)/bg092.tim bg092.lz
	cmplz $(TIM_DIR)/bg093.tim bg093.lz
	cmplz $(TIM_DIR)/bg094.tim bg094.lz
	cmplz $(TIM_DIR)/ki.tim ki.lz
	hdlink /n /l bg09t.lis
	rsdlink 092.rsd
	tmdsort -o 092.tmd a.tmd
	rsdlink 093.rsd
	tmdsort -o 093.tmd a.tmd
	hdlink /n /l bg09.lis
	cmplz bg09.mod  bg09.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
