TIM_DIR=..\tim
BG11_DIR=bg11y\rsd

all :
	cd $(BG11_DIR)
	timpos $(TIM_DIR)/bg112.tim   448  256    0 498
	timpos $(TIM_DIR)/bg113.tim   448  344    0 499
	timpos $(TIM_DIR)/ki.tim      576  256    0 500
	timpos $(TIM_DIR)/jimen.tim   576  344   16 500
	timpos $(TIM_DIR)/ki2.tim     598  256    0 501
	cmplz $(TIM_DIR)/bg112.tim   bg112.lz
	cmplz $(TIM_DIR)/bg113.tim   bg113.lz
	cmplz $(TIM_DIR)/ki.tim      ki.lz
	cmplz $(TIM_DIR)/jimen.tim   jimen.lz
	cmplz $(TIM_DIR)/ki2.tim     ki2.lz
	hdlink /n /l bg11t.lis
	rsdlink bg111.rsd
	tmdsort -o bg111.tmd a.tmd
	rsdlink bg112.rsd
	tmdsort -o bg112.tmd a.tmd
	hdlink /n /l bg11.lis
	cmplz bg11.mod  bg11.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
