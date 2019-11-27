ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
GRADIA_DIR=41\rsd
GRTOB_DIR=41tob\rsd

all : gr.mot gr1.mod gr2.mod
    psymake

gr1.mod: $(GRADIA_DIR)\gr1.lz $(GRTOB_DIR)\grtob1.lz
	hdlink /n /l gr1.lis

$(GRADIA_DIR)\gr1.lz:
	cd $(GRADIA_DIR)
	timpos $(TIM_DIR)/hara3.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448  80  32 482
	timpos $(TIM_DIR)/head2.tim   448 152  48 482
	timpos $(TIM_DIR)/head2b.tim  464 152  64 482
	timpos $(TIM_DIR)/head3.tim   480 152  80 482
	timpos $(TIM_DIR)/head4.tim   496 152  96 482
	timpos $(TIM_DIR)/headura.tim 512   0 112 482
	timpos $(TIM_DIR)/body.tim    512  96 128 482
	timpos $(TIM_DIR)/hane1.tim   512 160 144 482
	timpos $(TIM_DIR)/me.tim      542   0   0 480
	rsdlink grik.arg
	tmdsort -o gr1.tmd a.tmd
	cmplz gr1.tmd gr1.lz
	del a.tmd
	cd ..\..

$(GRTOB_DIR)\grtob1.lz:
	cd $(GRTOB_DIR)
	timpos $(TIM_DIR)/hara3.tim   448   0  16 482
	timpos $(TIM_DIR)/hara2.tim   448  80  32 482
	timpos $(TIM_DIR)/head2.tim   448 152  48 482
	timpos $(TIM_DIR)/head2b.tim  464 152  64 482
	timpos $(TIM_DIR)/head3.tim   480 152  80 482
	timpos $(TIM_DIR)/head4.tim   496 152  96 482
	timpos $(TIM_DIR)/headura.tim 512   0 112 482
	timpos $(TIM_DIR)/body.tim    512  96 128 482
	timpos $(TIM_DIR)/hane1.tim   512 160 144 482
	timpos $(TIM_DIR)/hara4.tim   526   0 160 482
	timpos $(TIM_DIR)/hane2.tim   526 192 176 482
	timpos $(TIM_DIR)/me.tim      542   0   0 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name41.tim     896   0   0 487
	timpos $(NAMEVS)/namevs41.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/head2b.tim  head2b.lz
	cmplz $(TIM_DIR)/head3.tim   head3.lz
	cmplz $(TIM_DIR)/head4.tim   head4.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name41.tim     name.lz
	cmplz $(NAMEVS)/namevs41.tim namevs.lz
	hdlink /n /l ..\..\gr1t.lis
	rsdlink 41tob.arg
	tmdsort -o grtob1.tmd a.tmd
	cmplz grtob1.tmd grtob1.lz
	del a.tmd
	cd ..\..

gr2.mod: $(GRADIA_DIR)\gr2.lz $(GRTOB_DIR)\grtob2.lz
	hdlink /n /l gr2.lis

$(GRADIA_DIR)\gr2.lz:
	cd $(GRADIA_DIR)
	timpos $(TIM_DIR)/hara3.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704  80  32 490
	timpos $(TIM_DIR)/head2.tim   704 152  48 490
	timpos $(TIM_DIR)/head2b.tim  720 152  64 490
	timpos $(TIM_DIR)/head3.tim   736 152  80 490
	timpos $(TIM_DIR)/head4.tim   752 152  96 490
	timpos $(TIM_DIR)/headura.tim 768   0 112 490
	timpos $(TIM_DIR)/body.tim    768  96 128 490
	timpos $(TIM_DIR)/hane1.tim   768 160 144 490
	timpos $(TIM_DIR)/me.tim      798   0   0 488
	rsdlink grik.arg
	tmdsort -o gr2.tmd a.tmd
	cmplz gr2.tmd gr2.lz
	del a.tmd
	cd ..\..

$(GRTOB_DIR)\grtob2.lz:
	cd $(GRTOB_DIR)
	timpos $(TIM_DIR)/hara3.tim   704   0  16 490
	timpos $(TIM_DIR)/hara2.tim   704  80  32 490
	timpos $(TIM_DIR)/head2.tim   704 152  48 490
	timpos $(TIM_DIR)/head2b.tim  720 152  64 490
	timpos $(TIM_DIR)/head3.tim   736 152  80 490
	timpos $(TIM_DIR)/head4.tim   752 152  96 490
	timpos $(TIM_DIR)/headura.tim 768   0 112 490
	timpos $(TIM_DIR)/body.tim    768  96 128 490
	timpos $(TIM_DIR)/hane1.tim   768 160 144 490
	timpos $(TIM_DIR)/hara4.tim   782   0 160 490
	timpos $(TIM_DIR)/hane2.tim   782 192 176 490
	timpos $(TIM_DIR)/me.tim      798   0   0 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name41.tim     926   0   0 495
	timpos $(NAMEVS)/namevs41.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/head2b.tim  head2b.lz
	cmplz $(TIM_DIR)/head3.tim   head3.lz
	cmplz $(TIM_DIR)/head4.tim   head4.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name41.tim     name.lz
	cmplz $(NAMEVS)/namevs41.tim namevs.lz
	hdlink /n /l ..\..\gr2t.lis
	rsdlink 41tob.arg
	tmdsort -o grtob2.tmd a.tmd
	cmplz grtob2.tmd grtob2.lz
	del a.tmd
	cd ..\..

gr.mot: $(GRADIA_DIR)\$(ANM_DIR)/griki.lz \
		$(GRTOB_DIR)\$(ANM_DIR)/41tos0.lz \
		$(GRTOB_DIR)\$(ANM_DIR)/41tos1.lz \
		$(GRTOB_DIR)\$(ANM_DIR)/41tos2.lz
	hdlink /n /l gr.lis

$(GRADIA_DIR)\$(ANM_DIR)/griki.lz:
	cd $(GRADIA_DIR)\$(ANM_DIR)
	bin2mtn griki
	cmplz griki.mtn griki.lz
	cd ..\..

$(GRTOB_DIR)\$(ANM_DIR)/41tos0.lz:
	cd $(GRTOB_DIR)\$(ANM_DIR)
	bin2mtn 41tos0
	cmplz 41tos0.mtn 41tos0.lz
	cd ..\..

$(GRTOB_DIR)\$(ANM_DIR)/41tos1.lz:
	cd $(GRTOB_DIR)\$(ANM_DIR)
	bin2mtn 41tos1
	cmplz 41tos1.mtn 41tos1.lz
	cd ..\..

$(GRTOB_DIR)\$(ANM_DIR)/41tos2.lz:
	cd $(GRTOB_DIR)\$(ANM_DIR)
	bin2mtn 41tos2
	cmplz 41tos2.mtn 41tos2.lz
	cd ..\..


