TIM_DIR=..\tim
BG97_DIR=bg97\rsd

all :
	cd $(BG97_DIR)
	timpos $(TIM_DIR)/back1.tim 320  256    0 497
	timpos $(TIM_DIR)/1.tim     576  256    0 498
	timpos $(TIM_DIR)/2.tim     576  320   16 498
	timpos $(TIM_DIR)/3.tim     576  384   32 498
	timpos $(TIM_DIR)/4.tim     576  448   80 498
	timpos $(TIM_DIR)/iwa.tim   592  256   48 498
	cmplz $(TIM_DIR)/back1.tim back1.lz
	cmplz $(TIM_DIR)/1.tim     1.lz
	cmplz $(TIM_DIR)/2.tim     2.lz
	cmplz $(TIM_DIR)/3.tim     3.lz
	cmplz $(TIM_DIR)/4.tim     4.lz
	cmplz $(TIM_DIR)/iwa.tim   iwa.lz
	hdlink /n /l bg97t.lis
	rsdlink bg97.rsd
	tmdsort -o bg97.tmd a.tmd
	hdlink /n /l bg97.lis
	cmplz bg97.mod  bg97.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
