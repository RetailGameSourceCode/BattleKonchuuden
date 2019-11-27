ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
OOKUWA_DIR=ookw\rsd
OKTOBI=oktos\rsd

all : ok.mot ok1.mod ok2.mod
    psymake

ok1.mod: $(OOKUWA_DIR)\ok1.lz $(OKTOBI)\oktob1.lz
	hdlink /n /l ok1.lis

$(OOKUWA_DIR)\ok1.lz:
	cd $(OOKUWA_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/mune.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  96  64 482
	timpos $(TIM_DIR)/hara4.tim   428   0  80 482
	timpos $(TIM_DIR)/hane1.tim   428 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/hara3.tim   448 112 128 482
	timpos $(TIM_DIR)/hane2.tim   448 192 144 482
	timpos $(TIM_DIR)/me.tim      502   0 160 482
	timpos $(TIM_DIR)/hara2.tim   512   0 176 482
	rsdlink ookw.arg
	tmdsort -o ok1.tmd a.tmd
	cmplz ok1.tmd ok1.lz
	del a.tmd
	cd ..\..

$(OKTOBI)\oktob1.lz:
	cd $(OKTOBI)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/mune.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  96  64 482
	timpos $(TIM_DIR)/hara4.tim   428   0  80 482
	timpos $(TIM_DIR)/hane1.tim   428 192  96 482
	timpos $(TIM_DIR)/head.tim    448   0 112 482
	timpos $(TIM_DIR)/hara3.tim   448 112 128 482
	timpos $(TIM_DIR)/hane2.tim   448 192 144 482
	timpos $(TIM_DIR)/me.tim      502   0 160 482
	timpos $(TIM_DIR)/hara2.tim   512   0 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name39.tim     896   0   0 487
	timpos $(NAMEVS)/namevs39.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name39.tim     name.lz
	cmplz $(NAMEVS)/namevs39.tim namevs.lz
	hdlink /n /l ..\..\ok1t.lis
	rsdlink oktos.arg
	tmdsort -o oktob1.tmd a.tmd
	cmplz oktob1.tmd oktob1.lz
	del a.tmd
	cd ..\..

ok2.mod: $(OOKUWA_DIR)\ok2.lz $(OKTOBI)\oktob2.lz
	hdlink /n /l ok2.lis

$(OOKUWA_DIR)\ok2.lz:
	cd $(OOKUWA_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/mune.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  96  64 490
	timpos $(TIM_DIR)/hara4.tim   684   0  80 490
	timpos $(TIM_DIR)/hane1.tim   684 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/hara3.tim   704 112 128 490
	timpos $(TIM_DIR)/hane2.tim   704 192 144 490
	timpos $(TIM_DIR)/me.tim      758   0 160 490
	timpos $(TIM_DIR)/hara2.tim   768   0 176 490
	rsdlink ookw.arg
	tmdsort -o ok2.tmd a.tmd
	cmplz ok2.tmd ok2.lz
	del a.tmd
	cd ..\..

$(OKTOBI)\oktob2.lz:
	cd $(OKTOBI)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/mune.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  96  64 490
	timpos $(TIM_DIR)/hara4.tim   684   0  80 490
	timpos $(TIM_DIR)/hane1.tim   684 192  96 490
	timpos $(TIM_DIR)/head.tim    704   0 112 490
	timpos $(TIM_DIR)/hara3.tim   704 112 128 490
	timpos $(TIM_DIR)/hane2.tim   704 192 144 490
	timpos $(TIM_DIR)/me.tim      758   0 160 490
	timpos $(TIM_DIR)/hara2.tim   768   0 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name39.tim     926   0   0 495
	timpos $(NAMEVS)/namevs39.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name39.tim     name.lz
	cmplz $(NAMEVS)/namevs39.tim namevs.lz
	hdlink /n /l ..\..\ok2t.lis
	rsdlink oktos.arg
	tmdsort -o oktob2.tmd a.tmd
	cmplz oktob2.tmd oktob2.lz
	del a.tmd
	cd ..\..

ok.mot: $(OOKUWA_DIR)\$(ANM_DIR)/okiki.lz
	hdlink /n /l ok.lis

$(OOKUWA_DIR)\$(ANM_DIR)/okiki.lz:
	cd $(OOKUWA_DIR)\$(ANM_DIR)
	bin2mtn okwiki
	cmplz okwiki.mtn okiki.lz
	cd ..\..


