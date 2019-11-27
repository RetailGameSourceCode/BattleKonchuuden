ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
GOHON_DIR=goiki\rsd
GOTOB_DIR=gotobi\rsd

all : go.mot go1.mod go2.mod
    psymake

go1.mod: $(GOHON_DIR)\go1.lz $(GOTOB_DIR)\gotobi1.lz
	hdlink /n /l go1.lis

$(GOHON_DIR)\go1.lz:
	cd $(GOHON_DIR)
	timpos $(TIM_DIR)/gohane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara3.tim   428   0 128 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 112 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 480
	timpos $(TIM_DIR)/hara1.tim   448  80  32 482
	timpos $(TIM_DIR)/me.tim      484  80  96 482
	timpos $(TIM_DIR)/hane2.tim   484 128  64 482
	timpos $(TIM_DIR)/hane1.tim   484 184  48 482
	timpos $(TIM_DIR)/hara2.tim   512   0  80 482
	timpos $(TIM_DIR)/at01.tim    512  72  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink goiki.arg
	tmdsort -o go1.tmd a.tmd
	cmplz go1.tmd go1.lz
	del a.tmd
	cd ..\..

$(GOTOB_DIR)\gotobi1.lz:
	cd $(GOTOB_DIR)
	timpos $(TIM_DIR)/gohane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara3.tim   428   0 128 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 112 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 480
	timpos $(TIM_DIR)/hara1.tim   448  80  32 482
	timpos $(TIM_DIR)/me.tim      484  80  96 482
	timpos $(TIM_DIR)/hane2.tim   484 128  64 482
	timpos $(TIM_DIR)/hane1.tim   484 184  48 482
	timpos $(TIM_DIR)/hara2.tim   512   0  80 482
	timpos $(TIM_DIR)/at01.tim    512  72  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name13.tim     896   0   0 487
	timpos $(NAMEVS)/namevs13.tim 896  16  16 487
	cmplz $(TIM_DIR)/gohane.tim  gohane.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name13.tim     name.lz
	cmplz $(NAMEVS)/namevs13.tim namevs.lz
	hdlink /n /l ..\..\go1t.lis
	rsdlink gotobi.arg
	tmdsort -o gotobi1.tmd a.tmd
	cmplz gotobi1.tmd gotobi1.lz
	del a.tmd
	cd ..\..

go2.mod: $(GOHON_DIR)\go2.lz $(GOTOB_DIR)\gotobi2.lz
	hdlink /n /l go2.lis

$(GOHON_DIR)\go2.lz:
	cd $(GOHON_DIR)
	timpos $(TIM_DIR)/gohane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara3.tim   684   0 128 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 112 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 488
	timpos $(TIM_DIR)/hara1.tim   704  80  32 490
	timpos $(TIM_DIR)/me.tim      740  80  96 490
	timpos $(TIM_DIR)/hane2.tim   740 128  64 490
	timpos $(TIM_DIR)/hane1.tim   740 184  48 490
	timpos $(TIM_DIR)/hara2.tim   768   0  80 490
	timpos $(TIM_DIR)/at01.tim    768  72  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink goiki.arg
	tmdsort -o go2.tmd a.tmd
	cmplz go2.tmd go2.lz
	del a.tmd
	cd ..\..

$(GOTOB_DIR)\gotobi2.lz:
	cd $(GOTOB_DIR)
	timpos $(TIM_DIR)/gohane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara3.tim   684   0 128 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 112 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 488
	timpos $(TIM_DIR)/hara1.tim   704  80  32 490
	timpos $(TIM_DIR)/me.tim      740  80  96 490
	timpos $(TIM_DIR)/hane2.tim   740 128  64 490
	timpos $(TIM_DIR)/hane1.tim   740 184  48 490
	timpos $(TIM_DIR)/hara2.tim   768   0  80 490
	timpos $(TIM_DIR)/at01.tim    768  72  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name13.tim     926   0   0 495
	timpos $(NAMEVS)/namevs13.tim 896  56  16 495
	cmplz $(TIM_DIR)/gohane.tim  gohane.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/at01.tim    at01.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name13.tim     name.lz
	cmplz $(NAMEVS)/namevs13.tim namevs.lz
	hdlink /n /l ..\..\go2t.lis
	rsdlink gotobi.arg
	tmdsort -o gotobi2.tmd a.tmd
	cmplz gotobi2.tmd gotobi2.lz
	del a.tmd
	cd ..\..

go.mot: $(GOHON_DIR)\$(ANM_DIR)/goiki.lz \
		$(GOTOB_DIR)\$(ANM_DIR)/gotob0.lz \
		$(GOTOB_DIR)\$(ANM_DIR)/gotob1.lz \
		$(GOHON_DIR)\$(ANM_DIR)/goatc1.lz \
		$(GOHON_DIR)\$(ANM_DIR)/goatc2.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom0.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom0m.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom1.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom1m.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom2.lz \
		$(GOHON_DIR)\$(ANM_DIR)/gocom2m.lz
	hdlink /n /l go.lis

$(GOHON_DIR)\$(ANM_DIR)/goiki.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn goiki
	cmplz goiki.mtn goiki.lz
	cd ..\..

$(GOTOB_DIR)\$(ANM_DIR)/gotob0.lz:
	cd $(GOTOB_DIR)\$(ANM_DIR)
	bin2mtn gotob0
	cmplz gotob0.mtn gotob0.lz
	cd ..\..

$(GOTOB_DIR)\$(ANM_DIR)/gotob1.lz:
	cd $(GOTOB_DIR)\$(ANM_DIR)
	bin2mtn gotob1
	cmplz gotob1.mtn gotob1.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/goatc1.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn goatc1
	cmplz goatc1.mtn goatc1.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/goatc2.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn goatc2
	cmplz goatc2.mtn goatc2.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom0.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom0
	cmplz gocom0.mtn gocom0.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom0m.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom0m
	cmplz gocom0m.mtn gocom0m.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom1.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom1
	cmplz gocom1.mtn gocom1.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom1m.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom1m
	cmplz gocom1m.mtn gocom1m.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom2.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom2
	cmplz gocom2.mtn gocom2.lz
	cd ..\..

$(GOHON_DIR)\$(ANM_DIR)/gocom2m.lz:
	cd $(GOHON_DIR)\$(ANM_DIR)
	bin2mtn gocom2m
	cmplz gocom2m.mtn gocom2m.lz
	cd ..\..


