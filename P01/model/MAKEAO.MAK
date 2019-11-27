ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
ATUSAM_DIR=30\rsd
ATUTOB_DIR=30tob\rsd

all : ao.mot ao1.mod ao2.mod
    psymake

ao1.mod: $(ATUSAM_DIR)\ao1.lz $(ATUTOB_DIR)\aotob1.lz
	hdlink /n /l ao1.lis

$(ATUSAM_DIR)\ao1.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/hara1.tim   384   0  16 482
	timpos $(TIM_DIR)/headura.tim 384 160  32 482
	timpos $(TIM_DIR)/hara4.tim   420   0  48 482
	timpos $(TIM_DIR)/hara2.tim   448   0  64 482
	timpos $(TIM_DIR)/hane1.tim   448  72  80 482
	timpos $(TIM_DIR)/doutai.tim  448 128  96 482
	timpos $(TIM_DIR)/hane2.tim   462  72 112 482
	timpos $(TIM_DIR)/head2.tim   480 128   0 480
	timpos $(TIM_DIR)/head.tim    480 192 128 482
	timpos $(TIM_DIR)/tono.tim    496 192 144 482
	rsdlink 30iki.arg
	tmdsort -o ao1.tmd a.tmd
	cmplz ao1.tmd ao1.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\aotob1.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/hara1.tim   384   0  16 482
	timpos $(TIM_DIR)/headura.tim 384 160  32 482
	timpos $(TIM_DIR)/hara4.tim   420   0  48 482
	timpos $(TIM_DIR)/hara2.tim   448   0  64 482
	timpos $(TIM_DIR)/hane1.tim   448  72  80 482
	timpos $(TIM_DIR)/doutai.tim  448 128  96 482
	timpos $(TIM_DIR)/hane2.tim   462  72 112 482
	timpos $(TIM_DIR)/head2.tim   480 128   0 480
	timpos $(TIM_DIR)/head.tim    480 192 128 482
	timpos $(TIM_DIR)/tono.tim    496 192 144 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name30.tim     896   0   0 487
	timpos $(NAMEVS)/namevs30.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name30.tim     name.lz
	cmplz $(NAMEVS)/namevs30.tim namevs.lz
	hdlink /n /l ..\..\ao1t.lis
	rsdlink 30tob.arg
	tmdsort -o aotob1.tmd a.tmd
	cmplz aotob1.tmd aotob1.lz
	del a.tmd
	cd ..\..

ao2.mod: $(ATUSAM_DIR)\ao2.lz $(ATUTOB_DIR)\aotob2.lz
	hdlink /n /l ao2.lis

$(ATUSAM_DIR)\ao2.lz:
	cd $(ATUSAM_DIR)
	timpos $(TIM_DIR)/hara1.tim   640   0  16 490
	timpos $(TIM_DIR)/headura.tim 640 160  32 490
	timpos $(TIM_DIR)/hara4.tim   676   0  48 490
	timpos $(TIM_DIR)/hara2.tim   704   0  64 490
	timpos $(TIM_DIR)/hane1.tim   704  72  80 490
	timpos $(TIM_DIR)/doutai.tim  704 128  96 490
	timpos $(TIM_DIR)/hane2.tim   718  72 112 490
	timpos $(TIM_DIR)/head2.tim   736 128   0 488
	timpos $(TIM_DIR)/head.tim    736 192 128 490
	timpos $(TIM_DIR)/tono.tim    752 192 144 490
	rsdlink 30iki.arg
	tmdsort -o ao2.tmd a.tmd
	cmplz ao2.tmd ao2.lz
	del a.tmd
	cd ..\..

$(ATUTOB_DIR)\aotob2.lz:
	cd $(ATUTOB_DIR)
	timpos $(TIM_DIR)/hara1.tim   640   0  16 490
	timpos $(TIM_DIR)/headura.tim 640 160  32 490
	timpos $(TIM_DIR)/hara4.tim   676   0  48 490
	timpos $(TIM_DIR)/hara2.tim   704   0  64 490
	timpos $(TIM_DIR)/hane1.tim   704  72  80 490
	timpos $(TIM_DIR)/doutai.tim  704 128  96 490
	timpos $(TIM_DIR)/hane2.tim   718  72 112 490
	timpos $(TIM_DIR)/head2.tim   736 128   0 488
	timpos $(TIM_DIR)/head.tim    736 192 128 490
	timpos $(TIM_DIR)/tono.tim    752 192 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name30.tim     926   0   0 495
	timpos $(NAMEVS)/namevs30.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name30.tim     name.lz
	cmplz $(NAMEVS)/namevs30.tim namevs.lz
	hdlink /n /l ..\..\ao2t.lis
	rsdlink 30tob.arg
	tmdsort -o aotob2.tmd a.tmd
	cmplz aotob2.tmd aotob2.lz
	del a.tmd
	cd ..\..

ao.mot: $(ATUSAM_DIR)\$(ANM_DIR)/30iki.lz
	hdlink /n /l ao.lis

$(ATUSAM_DIR)\$(ANM_DIR)/30iki.lz:
	cd $(ATUSAM_DIR)\$(ANM_DIR)
	bin2mtn 30iki
	cmplz 30iki.mtn 30iki.lz
	cd ..\..


