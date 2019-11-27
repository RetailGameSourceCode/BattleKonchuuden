ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
DAIOU_DIR=37\rsd
DAITOB_DIR=37tob\rsd

all : dh.mot dh1.mod dh2.mod
    psymake

dh1.mod: $(DAIOU_DIR)\dh1.lz $(DAITOB_DIR)\dhtob1.lz
	hdlink /n /l dh1.lis

$(DAIOU_DIR)\dh1.lz:
	cd $(DAIOU_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/mune.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  96  64 482
	timpos $(TIM_DIR)/head.tim    448   0  80 482
	timpos $(TIM_DIR)/hara3.tim   448 112  96 482
	timpos $(TIM_DIR)/me.tim      502   0 112 482
	timpos $(TIM_DIR)/hara2.tim   512   0 128 482
	rsdlink 37iki.arg
	tmdsort -o dh1.tmd a.tmd
	cmplz dh1.tmd dh1.lz
	del a.tmd
	cd ..\..

$(DAITOB_DIR)\dhtob1.lz:
	cd $(DAITOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/mune.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   384  96  64 482
	timpos $(TIM_DIR)/head.tim    448   0  80 482
	timpos $(TIM_DIR)/hara3.tim   448 112  96 482
	timpos $(TIM_DIR)/me.tim      502   0 112 482
	timpos $(TIM_DIR)/hara2.tim   512   0 128 482
	timpos $(TIM_DIR)/hara4.tim   428   0 144 482
	timpos $(TIM_DIR)/hane1.tim   428 192 160 482
	timpos $(TIM_DIR)/hane2.tim   448 192 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name37.tim     896   0   0 487
	timpos $(NAMEVS)/namevs37.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name37.tim     name.lz
	cmplz $(NAMEVS)/namevs37.tim namevs.lz
	hdlink /n /l ..\..\dh1t.lis
	rsdlink 37tob.arg
	tmdsort -o dhtob1.tmd a.tmd
	cmplz dhtob1.tmd dhtob1.lz
	del a.tmd
	cd ..\..

dh2.mod: $(DAIOU_DIR)\dh2.lz $(DAITOB_DIR)\dhtob2.lz
	hdlink /n /l dh2.lis

$(DAIOU_DIR)\dh2.lz:
	cd $(DAIOU_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/mune.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  96  64 490
	timpos $(TIM_DIR)/head.tim    704   0  80 490
	timpos $(TIM_DIR)/hara3.tim   704 112  96 490
	timpos $(TIM_DIR)/me.tim      758   0 112 490
	timpos $(TIM_DIR)/hara2.tim   768   0 128 490
	rsdlink 37iki.arg
	tmdsort -o dh2.tmd a.tmd
	cmplz dh2.tmd dh2.lz
	del a.tmd
	cd ..\..

$(DAITOB_DIR)\dhtob2.lz:
	cd $(DAITOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/mune.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   640  96  64 490
	timpos $(TIM_DIR)/head.tim    704   0  80 490
	timpos $(TIM_DIR)/hara3.tim   704 112  96 490
	timpos $(TIM_DIR)/me.tim      758   0 112 490
	timpos $(TIM_DIR)/hara2.tim   768   0 128 490
	timpos $(TIM_DIR)/hara4.tim   684   0 144 490
	timpos $(TIM_DIR)/hane1.tim   684 192 160 490
	timpos $(TIM_DIR)/hane2.tim   704 192 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name37.tim     926   0   0 495
	timpos $(NAMEVS)/namevs37.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name37.tim     name.lz
	cmplz $(NAMEVS)/namevs37.tim namevs.lz
	hdlink /n /l ..\..\dh2t.lis
	rsdlink 37tob.arg
	tmdsort -o dhtob2.tmd a.tmd
	cmplz dhtob2.tmd dhtob2.lz
	del a.tmd
	cd ..\..

dh.mot: $(DAIOU_DIR)\$(ANM_DIR)/37iki.lz
	hdlink /n /l dh.lis

$(DAIOU_DIR)\$(ANM_DIR)/37iki.lz:
	cd $(DAIOU_DIR)\$(ANM_DIR)
	bin2mtn 37iki
	cmplz 37iki.mtn 37iki.lz
	cd ..\..


