TIM_DIR=..\tim
BG04_DIR=bg04\rsd

all :
	cd $(BG04_DIR)
	timpos $(TIM_DIR)/bg041.tim 320  256    0 497
	timpos $(TIM_DIR)/bg043.tim 576  256    0 499
	timpos $(TIM_DIR)/bg044.tim 640  256    0 500
	timpos $(TIM_DIR)/ki02.tim  704  256   16 499
	cmplz $(TIM_DIR)/bg041.tim bg041.lz
	cmplz $(TIM_DIR)/bg043.tim bg043.lz
	cmplz $(TIM_DIR)/bg044.tim bg044.lz
	cmplz $(TIM_DIR)/ki02.tim  ki02.lz
	hdlink /n /l bg04t.lis
	rsdlink bg04.rsd
	tmdsort -o bg04.tmd a.tmd
	hdlink /n /l bg04.lis
	cmplz bg04.mod  bg04.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
