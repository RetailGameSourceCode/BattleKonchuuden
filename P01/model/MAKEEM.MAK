ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
EUROPE_DIR=28\rsd
EUROTOB_DIR=28tob\rsd

all : em.mot em1.mod em2.mod
    psymake

em1.mod: $(EUROPE_DIR)\em1.lz $(EUROTOB_DIR)\emtob1.lz
	hdlink /n /l em1.lis

$(EUROPE_DIR)\em1.lz:
	cd $(EUROPE_DIR)
	timpos $(TIM_DIR)/doutai.tim  384   0  16 482
	timpos $(TIM_DIR)/head2.tim   384 160  32 482
	timpos $(TIM_DIR)/hige.tim    384 224  48 482
	timpos $(TIM_DIR)/head.tim    400 160  64 482
	timpos $(TIM_DIR)/hara2.tim   416   0   0 480
	timpos $(TIM_DIR)/hara1.tim   416  72   0 481
	timpos $(TIM_DIR)/headura.tim 488 128  80 482
	timpos $(TIM_DIR)/tono.tim    502   0  96 482
	timpos $(TIM_DIR)/skin.tim    502  80 112 482
	timpos $(TIM_DIR)/me.tim      502 112 128 482
	rsdlink 28iki.arg
	tmdsort -o em1.tmd a.tmd
	cmplz em1.tmd em1.lz
	del a.tmd
	cd ..\..

$(EUROTOB_DIR)\emtob1.lz:
	cd $(EUROTOB_DIR)
	timpos $(TIM_DIR)/doutai.tim  384   0  16 482
	timpos $(TIM_DIR)/head2.tim   384 160  32 482
	timpos $(TIM_DIR)/hige.tim    384 224  48 482
	timpos $(TIM_DIR)/head.tim    400 160  64 482
	timpos $(TIM_DIR)/hara2.tim   416   0   0 480
	timpos $(TIM_DIR)/hara1.tim   416  72   0 481
	timpos $(TIM_DIR)/headura.tim 488 128  80 482
	timpos $(TIM_DIR)/tono.tim    502   0  96 482
	timpos $(TIM_DIR)/skin.tim    502  80 112 482
	timpos $(TIM_DIR)/me.tim      502 112 128 482
	timpos $(TIM_DIR)/hara4.tim   512   0 144 482
	timpos $(TIM_DIR)/hane1.tim   512 192 160 482
	timpos $(TIM_DIR)/hane2.tim   528   0 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name28.tim     896   0   0 487
	timpos $(NAMEVS)/namevs28.tim 896  16  16 487
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name28.tim     name.lz
	cmplz $(NAMEVS)/namevs28.tim namevs.lz
	hdlink /n /l ..\..\em1t.lis
	rsdlink 28tob.arg
	tmdsort -o emtob1.tmd a.tmd
	cmplz emtob1.tmd emtob1.lz
	del a.tmd
	cd ..\..

em2.mod: $(EUROPE_DIR)\em2.lz $(EUROTOB_DIR)\emtob2.lz
	hdlink /n /l em2.lis

$(EUROPE_DIR)\em2.lz:
	cd $(EUROPE_DIR)
	timpos $(TIM_DIR)/doutai.tim  640   0  16 490
	timpos $(TIM_DIR)/head2.tim   640 160  32 490
	timpos $(TIM_DIR)/hige.tim    640 224  48 490
	timpos $(TIM_DIR)/head.tim    656 160  64 490
	timpos $(TIM_DIR)/hara2.tim   672   0   0 488
	timpos $(TIM_DIR)/hara1.tim   672  72   0 489
	timpos $(TIM_DIR)/headura.tim 744 128  80 490
	timpos $(TIM_DIR)/tono.tim    758   0  96 490
	timpos $(TIM_DIR)/skin.tim    758  80 112 490
	timpos $(TIM_DIR)/me.tim      758 112 128 490
	rsdlink 28iki.arg
	tmdsort -o em2.tmd a.tmd
	cmplz em2.tmd em2.lz
	del a.tmd
	cd ..\..

$(EUROTOB_DIR)\emtob2.lz:
	cd $(EUROTOB_DIR)
	timpos $(TIM_DIR)/doutai.tim  640   0  16 490
	timpos $(TIM_DIR)/head2.tim   640 160  32 490
	timpos $(TIM_DIR)/hige.tim    640 224  48 490
	timpos $(TIM_DIR)/head.tim    656 160  64 490
	timpos $(TIM_DIR)/hara2.tim   672   0   0 488
	timpos $(TIM_DIR)/hara1.tim   672  72   0 489
	timpos $(TIM_DIR)/headura.tim 744 128  80 490
	timpos $(TIM_DIR)/tono.tim    758   0  96 490
	timpos $(TIM_DIR)/skin.tim    758  80 112 490
	timpos $(TIM_DIR)/me.tim      758 112 128 490
	timpos $(TIM_DIR)/hara4.tim   768   0 144 490
	timpos $(TIM_DIR)/hane1.tim   768 192 160 490
	timpos $(TIM_DIR)/hane2.tim   784   0 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name28.tim     926   0   0 495
	timpos $(NAMEVS)/namevs28.tim 896  56  16 495
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/head2.tim   head2.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tono.tim    tono.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name28.tim     name.lz
	cmplz $(NAMEVS)/namevs28.tim namevs.lz
	hdlink /n /l ..\..\em2t.lis
	rsdlink 28tob.arg
	tmdsort -o emtob2.tmd a.tmd
	cmplz emtob2.tmd emtob2.lz
	del a.tmd
	cd ..\..

em.mot: $(EUROPE_DIR)\$(ANM_DIR)/28iki.lz
	hdlink /n /l em.lis

$(EUROPE_DIR)\$(ANM_DIR)/28iki.lz:
	cd $(EUROPE_DIR)\$(ANM_DIR)
	bin2mtn 28iki
	cmplz 28iki.mtn 28iki.lz
	cd ..\..

