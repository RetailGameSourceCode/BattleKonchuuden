ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
HIRATA_DIR=38\rsd
HTTOB_DIR=38tob\rsd

all : ht.mot ht1.mod ht2.mod
    psymake

ht1.mod: $(HIRATA_DIR)\ht1.lz $(HTTOB_DIR)\httob1.lz
	hdlink /n /l ht1.lis

$(HIRATA_DIR)\ht1.lz:
	cd $(HIRATA_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/hane1.tim   362  96  48 482
	timpos $(TIM_DIR)/me.tim      376  96  64 482
	timpos $(TIM_DIR)/mune.tim    384   0  80 482
	timpos $(TIM_DIR)/hara1.tim   384  96  96 482
	timpos $(TIM_DIR)/hara4.tim   428   0 112 482
	timpos $(TIM_DIR)/head.tim    448   0 128 482
	timpos $(TIM_DIR)/hara3.tim   448 112 144 482
	timpos $(TIM_DIR)/hane2.tim   448 192 160 482
	timpos $(TIM_DIR)/hara2.tim   512   0 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name38.tim     896   0   0 487
	timpos $(NAMEVS)/namevs38.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name38.tim     name.lz
	cmplz $(NAMEVS)/namevs38.tim namevs.lz
	hdlink /n /l ..\..\ht1t.lis
	rsdlink hriki.arg
	tmdsort -o ht1.tmd a.tmd
	cmplz ht1.tmd ht1.lz
	del a.tmd
	cd ..\..

$(HTTOB_DIR)\httob1.lz:
	cd $(HTTOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0  16 482
	timpos $(TIM_DIR)/headura.tim 362   0  32 482
	timpos $(TIM_DIR)/hane1.tim   362  96  48 482
	timpos $(TIM_DIR)/me.tim      376  96  64 482
	timpos $(TIM_DIR)/mune.tim    384   0  80 482
	timpos $(TIM_DIR)/hara1.tim   384  96  96 482
	timpos $(TIM_DIR)/hara4.tim   428   0 112 482
	timpos $(TIM_DIR)/head.tim    448   0 128 482
	timpos $(TIM_DIR)/hara3.tim   448 112 144 482
	timpos $(TIM_DIR)/hane2.tim   448 192 160 482
	timpos $(TIM_DIR)/hara2.tim   512   0 176 482
	rsdlink 38tob.arg
	tmdsort -o httob1.tmd a.tmd
	cmplz httob1.tmd httob1.lz
	del a.tmd
	cd ..\..

ht2.mod: $(HIRATA_DIR)\ht2.lz $(HTTOB_DIR)\httob2.lz
	hdlink /n /l ht2.lis

$(HIRATA_DIR)\ht2.lz:
	cd $(HIRATA_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/hane1.tim   618  96  48 490
	timpos $(TIM_DIR)/me.tim      632  96  64 490
	timpos $(TIM_DIR)/mune.tim    640   0  80 490
	timpos $(TIM_DIR)/hara1.tim   640  96  96 490
	timpos $(TIM_DIR)/hara4.tim   684   0 112 490
	timpos $(TIM_DIR)/head.tim    704   0 128 490
	timpos $(TIM_DIR)/hara3.tim   704 112 144 490
	timpos $(TIM_DIR)/hane2.tim   704 192 160 490
	timpos $(TIM_DIR)/hara2.tim   768   0 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name38.tim     926   0   0 495
	timpos $(NAMEVS)/namevs38.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name38.tim     name.lz
	cmplz $(NAMEVS)/namevs38.tim namevs.lz
	hdlink /n /l ..\..\ht2t.lis
	rsdlink hriki.arg
	tmdsort -o ht2.tmd a.tmd
	cmplz ht2.tmd ht2.lz
	del a.tmd
	cd ..\..

$(HTTOB_DIR)\httob2.lz:
	cd $(HTTOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0  16 490
	timpos $(TIM_DIR)/headura.tim 618   0  32 490
	timpos $(TIM_DIR)/hane1.tim   618  96  48 490
	timpos $(TIM_DIR)/me.tim      632  96  64 490
	timpos $(TIM_DIR)/mune.tim    640   0  80 490
	timpos $(TIM_DIR)/hara1.tim   640  96  96 490
	timpos $(TIM_DIR)/hara4.tim   684   0 112 490
	timpos $(TIM_DIR)/head.tim    704   0 128 490
	timpos $(TIM_DIR)/hara3.tim   704 112 144 490
	timpos $(TIM_DIR)/hane2.tim   704 192 160 490
	timpos $(TIM_DIR)/hara2.tim   768   0 176 490
	rsdlink 38tob.arg
	tmdsort -o httob2.tmd a.tmd
	cmplz httob2.tmd httob2.lz
	del a.tmd
	cd ..\..

ht.mot: $(HIRATA_DIR)\$(ANM_DIR)/htiki.lz \
		$(HTTOB_DIR)\$(ANM_DIR)/httos0.lz \
		$(HTTOB_DIR)\$(ANM_DIR)/httos1.lz \
		$(HTTOB_DIR)\$(ANM_DIR)/httos2.lz
	hdlink /n /l ht.lis

$(HIRATA_DIR)\$(ANM_DIR)/htiki.lz:
	cd $(HIRATA_DIR)\$(ANM_DIR)
	bin2mtn hiraiki
	cmplz hiraiki.mtn htiki.lz
	cd ..\..

$(HTTOB_DIR)\$(ANM_DIR)/httos0.lz:
	cd $(HTTOB_DIR)\$(ANM_DIR)
	bin2mtn 38tos0
	cmplz 38tos0.mtn httos0.lz
	cd ..\..

$(HTTOB_DIR)\$(ANM_DIR)/httos1.lz:
	cd $(HTTOB_DIR)\$(ANM_DIR)
	bin2mtn 38tos1
	cmplz 38tos1.mtn httos1.lz
	cd ..\..

$(HTTOB_DIR)\$(ANM_DIR)/httos2.lz:
	cd $(HTTOB_DIR)\$(ANM_DIR)
	bin2mtn 38tos2
	cmplz 38tos2.mtn httos2.lz
	cd ..\..


