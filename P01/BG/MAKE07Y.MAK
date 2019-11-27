TIM_DIR=..\tim
BG07_DIR=bg07y\rsd

all :
	cd $(BG07_DIR)
	timpos $(TIM_DIR)/bg07.tim  320  256    0 497
	timpos $(TIM_DIR)/bg062.tim 448  256    0 498
	timpos $(TIM_DIR)/bg063.tim 448  384    0 499
	timpos $(TIM_DIR)/bg072.tim 448  256    0 501
	timpos $(TIM_DIR)/bg073.tim 448  384    0 502
	timpos $(TIM_DIR)/sora.tim  576  256    0 500
	timpos $(TIM_DIR)/mizu.tim  640  256   16 500
	timpos $(TIM_DIR)/kusa.tim  704  256   32 500
	timpos $(TIM_DIR)/kusa2.tim 704  384   48 500
	cmplz $(TIM_DIR)/bg07.tim bg06.lz
	cmplz $(TIM_DIR)/bg062.tim bg062.lz
	cmplz $(TIM_DIR)/bg063.tim bg063.lz
	cmplz $(TIM_DIR)/bg072.tim bg072.lz
	cmplz $(TIM_DIR)/bg073.tim bg073.lz
	cmplz $(TIM_DIR)/sora.tim ki02.lz
	cmplz $(TIM_DIR)/mizu.tim ki.lz
	cmplz $(TIM_DIR)/kusa.tim kusa.lz
	cmplz $(TIM_DIR)/kusa2.tim kusa2.lz
	hdlink /n /l bg07t.lis
	rsdlink bg07.rsd
	tmdsort -o bg07.tmd a.tmd
	rsdlink bg072.rsd
	tmdsort -o bg072.tmd a.tmd
	hdlink /n /l bg07.lis
	cmplz bg07.mod  bg07.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
