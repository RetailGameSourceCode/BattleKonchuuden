TIM_DIR=..\tim
BGLAST_DIR=bglast\rsd

all :
	cd $(BGLAST_DIR)
	timpos $(TIM_DIR)/last01.tim   320  256    0 497
	timpos $(TIM_DIR)/last02.tim   448  256    0 498
	timpos $(TIM_DIR)/ki.tim       576  256    0 499
	timpos $(TIM_DIR)/hikari.tim   576  344   16 499
	timpos $(TIM_DIR)/ki02.tim     576  408   32 499
	timpos $(TIM_DIR)/jimen.tim    598  256   48 499
	cmplz $(TIM_DIR)/last01.tim  last01.lz
	cmplz $(TIM_DIR)/last02.tim  last02.lz
	cmplz $(TIM_DIR)/ki.tim  ki.lz
	cmplz $(TIM_DIR)/hikari.tim  hikari.lz
	cmplz $(TIM_DIR)/ki02.tim  ki02.lz
	cmplz $(TIM_DIR)/jimen.tim jimen.lz
	hdlink /n /l bglastt.lis
	rsdlink bglast.rsd
	tmdsort -o bglast.tmd a.tmd
	rsdlink hikari.rsd
	tmdsort -o hikari.tmd a.tmd
	hdlink /n /l bglast.lis
	cmplz bglast.mod  bglast.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
