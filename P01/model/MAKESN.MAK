ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
SNIKI_DIR=sniki\rsd
SNTOBI_DIR=sntobi\rsd

all : sn.mot sn1.mod sn2.mod
    psymake

sn1.mod: $(SNIKI_DIR)\sn1.lz $(SNTOBI_DIR)\sntobi1.lz
	hdlink /n /l sn1.lis

$(SNIKI_DIR)\sn1.lz:
	cd $(SNIKI_DIR)
	timpos $(TIM_DIR)/gohane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara3.tim   428   0  32 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 128 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 480
	timpos $(TIM_DIR)/hara1.tim   448  80  16 482
	timpos $(TIM_DIR)/me.tim      484  80 112 482
	timpos $(TIM_DIR)/hane2.tim   484 128  80 482
	timpos $(TIM_DIR)/hane1.tim   484 184  64 482
	timpos $(TIM_DIR)/hara2.tim   512   0  96 482
	timpos $(TIM_DIR)/at01.tim    512  72  48 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink sniki.arg
	tmdsort -o sn1.tmd a.tmd
	cmplz sn1.tmd sn1.lz
	del a.tmd
	cd ..\..

$(SNTOBI_DIR)\sntobi1.lz:
	cd $(SNTOBI_DIR)
	timpos $(TIM_DIR)/gohane.tim  320   0   0 481
	timpos $(TIM_DIR)/hara3.tim   428   0  32 482
	timpos $(TIM_DIR)/syokaku.tim 428 192 128 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 480
	timpos $(TIM_DIR)/hara1.tim   448  80  16 482
	timpos $(TIM_DIR)/me.tim      484  80 112 482
	timpos $(TIM_DIR)/hane2.tim   484 128  80 482
	timpos $(TIM_DIR)/hane1.tim   484 184  64 482
	timpos $(TIM_DIR)/hara2.tim   512   0  96 482
	timpos $(TIM_DIR)/at01.tim    512  72  48 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name14.tim     896   0   0 487
	timpos $(NAMEVS)/namevs14.tim 896  16  16 487
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
	cmplz $(NAME)/name14.tim     name.lz
	cmplz $(NAMEVS)/namevs14.tim namevs.lz
	hdlink /n /l ..\..\sn1t.lis
	rsdlink sntobi.arg
	tmdsort -o sntobi1.tmd a.tmd
	cmplz sntobi1.tmd sntobi1.lz
	del a.tmd
	cd ..\..

sn2.mod: $(SNIKI_DIR)\sn2.lz $(SNTOBI_DIR)\sntobi2.lz
	hdlink /n /l sn2.lis

$(SNIKI_DIR)\sn2.lz:
	cd $(SNIKI_DIR)
	timpos $(TIM_DIR)/gohane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara3.tim   684   0  32 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 128 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 488
	timpos $(TIM_DIR)/hara1.tim   704  80  16 490
	timpos $(TIM_DIR)/me.tim      740  80 112 490
	timpos $(TIM_DIR)/hane2.tim   740 128  80 490
	timpos $(TIM_DIR)/hane1.tim   740 184  64 490
	timpos $(TIM_DIR)/hara2.tim   768   0  96 490
	timpos $(TIM_DIR)/at01.tim    768  72  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink sniki.arg
	tmdsort -o sn2.tmd a.tmd
	cmplz sn2.tmd sn2.lz
	del a.tmd
	cd ..\..

$(SNTOBI_DIR)\sntobi2.lz:
	cd $(SNTOBI_DIR)
	timpos $(TIM_DIR)/gohane.tim  576   0   0 489
	timpos $(TIM_DIR)/hara3.tim   684   0  32 490
	timpos $(TIM_DIR)/syokaku.tim 684 192 128 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 488
	timpos $(TIM_DIR)/hara1.tim   704  80  16 490
	timpos $(TIM_DIR)/me.tim      740  80 112 490
	timpos $(TIM_DIR)/hane2.tim   740 128  80 490
	timpos $(TIM_DIR)/hane1.tim   740 184  64 490
	timpos $(TIM_DIR)/hara2.tim   768   0  96 490
	timpos $(TIM_DIR)/at01.tim    768  72  48 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name14.tim     926   0   0 495
	timpos $(NAMEVS)/namevs14.tim 896  56  16 495
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
	cmplz $(NAME)/name14.tim     name.lz
	cmplz $(NAMEVS)/namevs14.tim namevs.lz
	hdlink /n /l ..\..\sn2t.lis
	rsdlink sntobi.arg
	tmdsort -o sntobi2.tmd a.tmd
	cmplz sntobi2.tmd sntobi2.lz
	del a.tmd
	cd ..\..

sn.mot: $(SNIKI_DIR)\$(ANM_DIR)/sniki.lz \
		$(SNTOBI_DIR)\$(ANM_DIR)/sntob0.lz \
		$(SNTOBI_DIR)\$(ANM_DIR)/sntob1.lz
	hdlink /n /l sn.lis

$(SNIKI_DIR)\$(ANM_DIR)/sniki.lz:
	cd $(SNIKI_DIR)\$(ANM_DIR)
	bin2mtn sniki
	cmplz sniki.mtn sniki.lz
	cd ..\..

$(SNTOBI_DIR)\$(ANM_DIR)/sntob0.lz:
	cd $(SNTOBI_DIR)\$(ANM_DIR)
	bin2mtn sntob0
	cmplz sntob0.mtn sntob0.lz
	cd ..\..

$(SNTOBI_DIR)\$(ANM_DIR)/sntob1.lz:
	cd $(SNTOBI_DIR)\$(ANM_DIR)
	bin2mtn sntob1
	cmplz sntob1.mtn sntob1.lz
	cd ..\..

