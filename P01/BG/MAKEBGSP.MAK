TIM_DIR=..\tim
BGLAST_DIR=bgsp\rsd

all :
	cd $(BGLAST_DIR)
	timpos $(TIM_DIR)/bgsp.tim     320  256    0 497
	timpos $(TIM_DIR)/jimen.tim    576  256    0 499
	timpos $(TIM_DIR)/jimen02.tim  576  320   16 499
	cmplz $(TIM_DIR)/bgsp.tim     bgsp.lz
	cmplz $(TIM_DIR)/jimen.tim    jimen.lz
	cmplz $(TIM_DIR)/jimen02.tim  jimen02.lz
	hdlink /n /l bgspt.lis
	rsdlink bgsp.rsd
	tmdsort -o bgsp.tmd a.tmd
	rsdlink bgsp02.rsd
	tmdsort -o bgsp02.tmd a.tmd
	rsdlink bgsp03.rsd
	tmdsort -o bgsp03.tmd a.tmd
	hdlink /n /l bgsp.lis
	cmplz bgsp.mod  bgsp.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
