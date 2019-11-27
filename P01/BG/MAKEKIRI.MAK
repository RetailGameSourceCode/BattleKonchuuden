TIM_DIR=..\tim
KIRI_DIR=kirikabu\rsd

all :
	cd $(KIRI_DIR)
	timpos $(TIM_DIR)/bg01.tim  320  256    0 497
	timpos $(TIM_DIR)/ki2.tim   576  256    0 498
	timpos $(TIM_DIR)/ki.tim    704  256    0 499
	cmplz $(TIM_DIR)/bg01.tim  bg01.lz
	cmplz $(TIM_DIR)/ki2.tim   ki2.lz
	cmplz $(TIM_DIR)/ki.tim    ki.lz
	hdlink /n /l kirit.lis
	rsdlink ki2.rsd
	tmdsort -o ki2.tmd a.tmd
	hdlink /n /l kiri.lis
	cmplz kiri.mod  kiri.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt

