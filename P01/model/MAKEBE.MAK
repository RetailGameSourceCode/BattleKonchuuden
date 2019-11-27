ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=49\rsd

all : be.mot be1.mod be2.mod
    psymake

be1.mod: $(RSD_DIR)\be1.lz
	hdlink /n /l be1.lis

$(RSD_DIR)\be1.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name44.tim     896   0   0 487
	timpos $(NAMEVS)/namevs44.tim 896  16  16 487
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name44.tim     name.lz
	cmplz $(NAMEVS)/namevs44.tim namevs.lz
	hdlink /n /l ..\..\be1t.lis
	rsdlink 49hci.arg
	tmdsort -o be1.tmd a.tmd
	cmplz be1.tmd be1.lz
	del a.tmd
	cd ..\..

be2.mod: $(RSD_DIR)\be2.lz
	hdlink /n /l be2.lis

$(RSD_DIR)\be2.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name44.tim     926   0   0 495
	timpos $(NAMEVS)/namevs44.tim 896  56  16 495
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name44.tim     name.lz
	cmplz $(NAMEVS)/namevs44.tim namevs.lz
	hdlink /n /l ..\..\be2t.lis
	rsdlink 49hci.arg
	tmdsort -o be2.tmd a.tmd
	cmplz be2.tmd be2.lz
	del a.tmd
	cd ..\..

be.mot: $(RSD_DIR)\$(ANM_DIR)/49iki.lz
	hdlink /n /l be.lis

$(RSD_DIR)\$(ANM_DIR)/49iki.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 49iki
	cmplz 49iki.mtn 49iki.lz
	cd ..\..


