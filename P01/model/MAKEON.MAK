ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
OOGON_DIR=40\rsd
ONTOB_DIR=40tob\rsd

all : on.mot on1.mod on2.mod
    psymake

on1.mod: $(OOGON_DIR)\on1.lz $(ONTOB_DIR)\ontob1.lz
	hdlink /n /l on1.lis

$(OOGON_DIR)\on1.lz:
	cd $(OOGON_DIR)
	timpos $(TIM_DIR)/tsuno3.tim  320   0  80 482
	timpos $(TIM_DIR)/tsuno2.tim  320 104  96 482
	timpos $(TIM_DIR)/body7.tim   384   0   0 480
	timpos $(TIM_DIR)/face.tim    470   0  64 482
	timpos $(TIM_DIR)/hara2       470  96 112 482
	timpos $(TIM_DIR)/onaka2.tim  488 128  48 482
	timpos $(TIM_DIR)/head4.tim   502   0   0 483
	timpos $(TIM_DIR)/mune3.tim   512  96   0 481
	timpos $(TIM_DIR)/muneura2.tim 538   0  32 482
	rsdlink ooniki.arg
	tmdsort -o on1.tmd a.tmd
	cmplz on1.tmd on1.lz
	del a.tmd
	cd ..\..

$(ONTOB_DIR)\ontob1.lz:
	cd $(ONTOB_DIR)
	timpos $(TIM_DIR)/tsuno3.tim  320   0  80 482
	timpos $(TIM_DIR)/tsuno2.tim  320 104  96 482
	timpos $(TIM_DIR)/body7.tim   384   0   0 480
	timpos $(TIM_DIR)/face.tim    470   0  64 482
	timpos $(TIM_DIR)/hara2       470  96 112 482
	timpos $(TIM_DIR)/onaka2.tim  488 128  48 482
	timpos $(TIM_DIR)/hane2.tim   488 200 128 482
	timpos $(TIM_DIR)/head4.tim   502   0   0 483
	timpos $(TIM_DIR)/mune3.tim   512  96   0 481
	timpos $(TIM_DIR)/hane1.tim   512 192 144 482
	timpos $(TIM_DIR)/muneura2.tim 538   0  32 482
	timpos $(TIM_DIR)/hara4.tim   560   0  16 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name40.tim     896   0   0 487
	timpos $(NAMEVS)/namevs40.tim 896  16  16 487
	cmplz $(TIM_DIR)/tsuno3.tim  tsuno3.lz
	cmplz $(TIM_DIR)/tsuno2.tim  tsuno2.lz
	cmplz $(TIM_DIR)/body7.tim   body7.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/onaka2.tim  onaka2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/head4.tim   head4.lz
	cmplz $(TIM_DIR)/mune3.tim   mune3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/muneura2.tim muneura2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name40.tim     name.lz
	cmplz $(NAMEVS)/namevs40.tim namevs.lz
	hdlink /n /l ..\..\on1t.lis
	rsdlink 40tob.arg
	tmdsort -o ontob1.tmd a.tmd
	cmplz ontob1.tmd ontob1.lz
	del a.tmd
	cd ..\..

on2.mod: $(OOGON_DIR)\on2.lz $(ONTOB_DIR)\ontob2.lz
	hdlink /n /l on2.lis

$(OOGON_DIR)\on2.lz:
	cd $(OOGON_DIR)
	timpos $(TIM_DIR)/tsuno3.tim  576   0  80 490
	timpos $(TIM_DIR)/tsuno2.tim  576 104  96 490
	timpos $(TIM_DIR)/body7.tim   640   0   0 488
	timpos $(TIM_DIR)/face.tim    726   0  64 490
	timpos $(TIM_DIR)/hara2       726  96 112 490
	timpos $(TIM_DIR)/onaka2.tim  744 128  48 490
	timpos $(TIM_DIR)/head4.tim   758   0   0 491
	timpos $(TIM_DIR)/mune3.tim   768  96   0 489
	timpos $(TIM_DIR)/muneura2.tim 794   0  32 490
	rsdlink ooniki.arg
	tmdsort -o on2.tmd a.tmd
	cmplz on2.tmd on2.lz
	del a.tmd
	cd ..\..

$(ONTOB_DIR)\ontob2.lz:
	cd $(ONTOB_DIR)
	timpos $(TIM_DIR)/tsuno3.tim  576   0  80 490
	timpos $(TIM_DIR)/tsuno2.tim  576 104  96 490
	timpos $(TIM_DIR)/body7.tim   640   0   0 488
	timpos $(TIM_DIR)/face.tim    726   0  64 490
	timpos $(TIM_DIR)/hara2       726  96 112 490
	timpos $(TIM_DIR)/onaka2.tim  744 128  48 490
	timpos $(TIM_DIR)/hane2.tim   744 200 128 490
	timpos $(TIM_DIR)/head4.tim   758   0   0 491
	timpos $(TIM_DIR)/mune3.tim   768  96   0 489
	timpos $(TIM_DIR)/hane1.tim   768 192 144 490
	timpos $(TIM_DIR)/muneura2.tim 794   0  32 490
	timpos $(TIM_DIR)/hara4.tim   816   0  16 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name40.tim     926   0   0 495
	timpos $(NAMEVS)/namevs40.tim 896  56  16 495
	cmplz $(TIM_DIR)/tsuno3.tim  tsuno3.lz
	cmplz $(TIM_DIR)/tsuno2.tim  tsuno2.lz
	cmplz $(TIM_DIR)/body7.tim   body7.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/onaka2.tim  onaka2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/head4.tim   head4.lz
	cmplz $(TIM_DIR)/mune3.tim   mune3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/muneura2.tim muneura2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name40.tim     name.lz
	cmplz $(NAMEVS)/namevs40.tim namevs.lz
	hdlink /n /l ..\..\on2t.lis
	rsdlink 40tob.arg
	tmdsort -o ontob2.tmd a.tmd
	cmplz ontob2.tmd ontob2.lz
	del a.tmd
	cd ..\..

on.mot: $(OOGON_DIR)\$(ANM_DIR)/ooniki.lz \
		$(ONTOB_DIR)\$(ANM_DIR)/40tos0.lz \
		$(ONTOB_DIR)\$(ANM_DIR)/40tos1.lz \
		$(ONTOB_DIR)\$(ANM_DIR)/40tos2.lz
	hdlink /n /l on.lis

$(OOGON_DIR)\$(ANM_DIR)/ooniki.lz:
	cd $(OOGON_DIR)\$(ANM_DIR)
	bin2mtn ooniki
	cmplz ooniki.mtn ooniki.lz
	cd ..\..

$(ONTOB_DIR)\$(ANM_DIR)/40tos0.lz:
	cd $(ONTOB_DIR)\$(ANM_DIR)
	bin2mtn 40tos0
	cmplz 40tos0.mtn 40tos0.lz
	cd ..\..

$(ONTOB_DIR)\$(ANM_DIR)/40tos1.lz:
	cd $(ONTOB_DIR)\$(ANM_DIR)
	bin2mtn 40tos1
	cmplz 40tos1.mtn 40tos1.lz
	cd ..\..

$(ONTOB_DIR)\$(ANM_DIR)/40tos2.lz:
	cd $(ONTOB_DIR)\$(ANM_DIR)
	bin2mtn 40tos2
	cmplz 40tos2.mtn 40tos2.lz
	cd ..\..


