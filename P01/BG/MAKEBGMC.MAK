TIM_DIR=..\tim
BGLAST_DIR=bgmachi\rsd

all :
	cd $(BGLAST_DIR)
	timpos $(TIM_DIR)/jimen02.tim  320  256   96 499
	timpos $(TIM_DIR)/bill04.tim   320  320   16 499
	timpos $(TIM_DIR)/bill05.tim   320  368   32 499
	timpos $(TIM_DIR)/bill01.tim   332  320   48 499
	timpos $(TIM_DIR)/bill02.tim   332  368   64 499
	timpos $(TIM_DIR)/bill03.tim   332  400   80 499
	timpos $(TIM_DIR)/jale01.tim   344  256  112 499
	timpos $(TIM_DIR)/jale02.tim   344  320  128 499
	timpos $(TIM_DIR)/ue01.tim     364  256  144 499
	timpos $(TIM_DIR)/ue02.tim     364  288  160 499
	timpos $(TIM_DIR)/ue03.tim     364  320  176 499
	timpos $(TIM_DIR)/hasi.tim     364  352  192 499
	timpos $(TIM_DIR)/bg01.tim     384  256    0 497
	timpos $(TIM_DIR)/jimen01.tim  384  384    0 499
	cmplz $(TIM_DIR)/jimen02.tim  jimen02.lz
	cmplz $(TIM_DIR)/bill01.tim   bill01.lz
	cmplz $(TIM_DIR)/bill02.tim   bill02.lz
	cmplz $(TIM_DIR)/bill03.tim   bill03.lz
	cmplz $(TIM_DIR)/bill04.tim   bill04.lz
	cmplz $(TIM_DIR)/bill05.tim   bill05.lz
	cmplz $(TIM_DIR)/jale01.tim   jale01.lz
	cmplz $(TIM_DIR)/jale02.tim   jale02.lz
	cmplz $(TIM_DIR)/ue01.tim     ue01.lz
	cmplz $(TIM_DIR)/ue02.tim     ue02.lz
	cmplz $(TIM_DIR)/ue03.tim     ue03.lz
	cmplz $(TIM_DIR)/hasi.tim     hasi.lz
	cmplz $(TIM_DIR)/bg01.tim     bg01.lz
	cmplz $(TIM_DIR)/jimen01.tim  jimen01.lz
	hdlink /n /l bgmachit.lis
	rsdlink machi.rsd
	tmdsort -o machi.tmd a.tmd
	rsdlink jimenn.rsd
	tmdsort -o jimenn.tmd a.tmd
	hdlink /n /l bgmachi.lis
	cmplz bgmachi.mod  bgmachi.a
	del a.tmd
	del *.lz
	cd ..\..
	filecat bg.lst bg.dat
	copy bg.dat d:\98025\dt
