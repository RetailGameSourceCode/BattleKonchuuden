ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
HOKBT_DIR=ookbt\rsd
HOTOB_DIR=ootob\rsd

all : ho.mot ho1.mod ho2.mod
    psymake

ho1.mod: $(HOKBT_DIR)\ho1.lz $(HOTOB_DIR)\hotob1.lz
	hdlink /n /l ho1.lis

$(HOKBT_DIR)\ho1.lz:
	cd $(HOKBT_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  80 482
	timpos $(TIM_DIR)/tuno.tim    376   0 160 482
	timpos $(TIM_DIR)/me.tim      376  96 176 482
	timpos $(TIM_DIR)/hara1.tim   384   0  32 482
	timpos $(TIM_DIR)/hara3.tim   384 160  64 482
	timpos $(TIM_DIR)/hara4.tim   428   0  16 482
	timpos $(TIM_DIR)/hige.tim    428 192 128 482
	timpos $(TIM_DIR)/head.tim    448   0  96 482
	timpos $(TIM_DIR)/hara2.tim   448 112  48 482
	timpos $(TIM_DIR)/syokaku.tim 448 184   0 480
	timpos $(TIM_DIR)/kuti.tim    492 128 144 482
	timpos $(TIM_DIR)/headura.tim 512   0 112 482
	rsdlink ookbt.arg
	tmdsort -o ho1.tmd a.tmd
	cmplz ho1.tmd ho1.lz
	del a.tmd
	cd ..\..

$(HOTOB_DIR)\hotob1.lz:
	cd $(HOTOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  80 482
	timpos $(TIM_DIR)/tuno.tim    376   0 160 482
	timpos $(TIM_DIR)/me.tim      376  96 176 482
	timpos $(TIM_DIR)/hara1.tim   384   0  32 482
	timpos $(TIM_DIR)/hara3.tim   384 160  64 482
	timpos $(TIM_DIR)/hara4.tim   428   0  16 482
	timpos $(TIM_DIR)/hige.tim    428 192 128 482
	timpos $(TIM_DIR)/head.tim    448   0  96 482
	timpos $(TIM_DIR)/hara2.tim   448 112  48 482
	timpos $(TIM_DIR)/syokaku.tim 448 184   0 480
	timpos $(TIM_DIR)/kuti.tim    492 128 144 482
	timpos $(TIM_DIR)/headura.tim 512   0 112 482
	timpos $(TIM_DIR)/hane1.tim   464 184 192 482
	timpos $(TIM_DIR)/hane2.tim   478 184 208 482
	timpos $(TIM_DIR)/mune.tim    512  96 224 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name21.tim     896   0   0 487
	timpos $(NAMEVS)/namevs21.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name21.tim     name.lz
	cmplz $(NAMEVS)/namevs21.tim namevs.lz
	hdlink /n /l ..\..\ho1t.lis
	rsdlink hotos.arg
	tmdsort -o hotob1.tmd a.tmd
	cmplz hotob1.tmd hotob1.lz
	del a.tmd
	cd ..\..

ho2.mod: $(HOKBT_DIR)\ho2.lz $(HOTOB_DIR)\hotob2.lz
	hdlink /n /l ho2.lis

$(HOKBT_DIR)\ho2.lz:
	cd $(HOKBT_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  80 490
	timpos $(TIM_DIR)/tuno.tim    632   0 160 490
	timpos $(TIM_DIR)/me.tim      632  96 176 490
	timpos $(TIM_DIR)/hara1.tim   640   0  32 490
	timpos $(TIM_DIR)/hara3.tim   640 160  64 490
	timpos $(TIM_DIR)/hara4.tim   684   0  16 490
	timpos $(TIM_DIR)/hige.tim    684 192 128 490
	timpos $(TIM_DIR)/head.tim    704   0  96 490
	timpos $(TIM_DIR)/hara2.tim   704 112  48 490
	timpos $(TIM_DIR)/syokaku.tim 704 184   0 488
	timpos $(TIM_DIR)/kuti.tim    748 128 144 490
	timpos $(TIM_DIR)/headura.tim 768   0 112 490
	rsdlink ookbt.arg
	tmdsort -o ho2.tmd a.tmd
	cmplz ho2.tmd ho2.lz
	del a.tmd
	cd ..\..

$(HOTOB_DIR)\hotob2.lz:
	cd $(HOTOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  80 490
	timpos $(TIM_DIR)/tuno.tim    632   0 160 490
	timpos $(TIM_DIR)/me.tim      632  96 176 490
	timpos $(TIM_DIR)/hara1.tim   640   0  32 490
	timpos $(TIM_DIR)/hara3.tim   640 160  64 490
	timpos $(TIM_DIR)/hara4.tim   684   0  16 490
	timpos $(TIM_DIR)/hige.tim    684 192 128 490
	timpos $(TIM_DIR)/head.tim    704   0  96 490
	timpos $(TIM_DIR)/hara2.tim   704 112  48 490
	timpos $(TIM_DIR)/syokaku.tim 704 184   0 488
	timpos $(TIM_DIR)/kuti.tim    748 128 144 490
	timpos $(TIM_DIR)/headura.tim 768   0 112 490
	timpos $(TIM_DIR)/hane1.tim   720 184 192 490
	timpos $(TIM_DIR)/hane2.tim   734 184 208 490
	timpos $(TIM_DIR)/mune.tim    768  96 224 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name21.tim     926   0   0 495
	timpos $(NAMEVS)/namevs21.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/kuti.tim    kuti.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name21.tim     name.lz
	cmplz $(NAMEVS)/namevs21.tim namevs.lz
	hdlink /n /l ..\..\ho2t.lis
	rsdlink hotos.arg
	tmdsort -o hotob2.tmd a.tmd
	cmplz hotob2.tmd hotob2.lz
	del a.tmd
	cd ..\..

ho.mot: $(HOKBT_DIR)\$(ANM_DIR)/hoik.lz \
		$(HOTOB_DIR)\$(ANM_DIR)/ootos0.lz \
		$(HOTOB_DIR)\$(ANM_DIR)/ootos1.lz \
		$(HOTOB_DIR)\$(ANM_DIR)/ootos2.lz
	hdlink /n /l ho.lis

$(HOKBT_DIR)\$(ANM_DIR)/hoik.lz:
	cd $(HOKBT_DIR)\$(ANM_DIR)
	bin2mtn ooiki
	cmplz ooiki.mtn hoik.lz
	cd ..\..

$(HOTOB_DIR)\$(ANM_DIR)/ootos0.lz:
	cd $(HOTOB_DIR)\$(ANM_DIR)
	bin2mtn ootos0
	cmplz ootos0.mtn ootos0.lz
	cd ..\..

$(HOTOB_DIR)\$(ANM_DIR)/ootos1.lz:
	cd $(HOTOB_DIR)\$(ANM_DIR)
	bin2mtn ootos1
	cmplz ootos1.mtn ootos1.lz
	cd ..\..

$(HOTOB_DIR)\$(ANM_DIR)/ootos2.lz:
	cd $(HOTOB_DIR)\$(ANM_DIR)
	bin2mtn ootos2
	cmplz ootos2.mtn ootos2.lz
	cd ..\..


