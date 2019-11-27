ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=48\rsd
RSDTOB_DIR=48tob\rsd

all : k2.mot k21.mod k22.mod
    psymake

k21.mod: $(RSD_DIR)\k21.lz $(RSDTOB_DIR)\k2tob1.lz
	hdlink /n /l k21.lis

$(RSD_DIR)\k21.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/hara2.tim   448 128  32 482
	timpos $(TIM_DIR)/tume.tim    464   0  48 482
	timpos $(TIM_DIR)/hane.tim    464  32  64 482
	timpos $(TIM_DIR)/hane2.tim   464  96  80 482
	timpos $(TIM_DIR)/doutai.tim  464 160  96 482
	timpos $(TIM_DIR)/skin.tim    464 224 112 482
	timpos $(TIM_DIR)/face.tim    472  32 128 482
	timpos $(TIM_DIR)/me.tim      472  64 144 482
	timpos $(TIM_DIR)/tuno2.tim   472  96 160 482
	timpos $(TIM_DIR)/tuno.tim    472 128 176 482
	timpos $(TIM_DIR)/hara.tim    480 128   0 480
	timpos $(TIM_DIR)/hara5.tim   544   0   0 484
	rsdlink 48iki.arg
	tmdsort -o k21.tmd a.tmd
	cmplz k21.tmd k21.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\k2tob1.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   448 128  32 482
	timpos $(TIM_DIR)/tume.tim    464   0  48 482
	timpos $(TIM_DIR)/hane.tim    464  32  64 482
	timpos $(TIM_DIR)/hane2.tim   464  96  80 482
	timpos $(TIM_DIR)/doutai.tim  464 160  96 482
	timpos $(TIM_DIR)/skin.tim    464 224 112 482
	timpos $(TIM_DIR)/face.tim    472  32 128 482
	timpos $(TIM_DIR)/me.tim      472  64 144 482
	timpos $(TIM_DIR)/tuno2.tim   472  96 160 482
	timpos $(TIM_DIR)/tuno.tim    472 128 176 482
	timpos $(TIM_DIR)/hara.tim    480 128   0 480
	timpos $(TIM_DIR)/hara3.tim   512   0   0 481
	timpos $(TIM_DIR)/hara4.tim   512 128   0 483
	timpos $(TIM_DIR)/hara5.tim   544   0   0 484
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name48.tim     896   0   0 487
	timpos $(NAMEVS)/namevs48.tim 896  16  16 487
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara5.tim   hara5.lz
	cmplz $(TIM_DIR)/tume.tim    tume.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno2.tim   tuno2.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name48.tim     name.lz
	cmplz $(NAMEVS)/namevs48.tim namevs.lz
	hdlink /n /l ..\..\k21t.lis
	rsdlink 48tob.arg
	tmdsort -o k2tob1.tmd a.tmd
	cmplz k2tob1.tmd k2tob1.lz
	del a.tmd
	cd ..\..

k22.mod: $(RSD_DIR)\k22.lz $(RSDTOB_DIR)\k2tob2.lz
	hdlink /n /l k22.lis

$(RSD_DIR)\k22.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/hara2.tim   704 128  32 490
	timpos $(TIM_DIR)/tume.tim    720   0  48 490
	timpos $(TIM_DIR)/hane.tim    720  32  64 490
	timpos $(TIM_DIR)/hane2.tim   720  96  80 490
	timpos $(TIM_DIR)/doutai.tim  720 160  96 490
	timpos $(TIM_DIR)/skin.tim    720 224 112 490
	timpos $(TIM_DIR)/face.tim    728  32 128 490
	timpos $(TIM_DIR)/me.tim      728  64 144 490
	timpos $(TIM_DIR)/tuno2.tim   728  96 160 490
	timpos $(TIM_DIR)/tuno.tim    728 128 176 490
	timpos $(TIM_DIR)/hara.tim    736 128   0 488
	timpos $(TIM_DIR)/hara5.tim   800   0   0 492
	rsdlink 48iki.arg
	tmdsort -o k22.tmd a.tmd
	cmplz k22.tmd k22.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\k2tob2.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/hara2.tim   704 128  32 490
	timpos $(TIM_DIR)/tume.tim    720   0  48 490
	timpos $(TIM_DIR)/hane.tim    720  32  64 490
	timpos $(TIM_DIR)/hane2.tim   720  96  80 490
	timpos $(TIM_DIR)/doutai.tim  720 160  96 490
	timpos $(TIM_DIR)/skin.tim    720 224 112 490
	timpos $(TIM_DIR)/face.tim    728  32 128 490
	timpos $(TIM_DIR)/me.tim      728  64 144 490
	timpos $(TIM_DIR)/tuno2.tim   728  96 160 490
	timpos $(TIM_DIR)/tuno.tim    728 128 176 490
	timpos $(TIM_DIR)/hara.tim    736 128   0 488
	timpos $(TIM_DIR)/hara3.tim   768   0   0 489
	timpos $(TIM_DIR)/hara4.tim   768 128   0 491
	timpos $(TIM_DIR)/hara5.tim   800   0   0 492
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name48.tim     926   0   0 495
	timpos $(NAMEVS)/namevs48.tim 896  56  16 495
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara5.tim   hara5.lz
	cmplz $(TIM_DIR)/tume.tim    tume.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/tuno2.tim   tuno2.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name48.tim     name.lz
	cmplz $(NAMEVS)/namevs48.tim namevs.lz
	hdlink /n /l ..\..\k22t.lis
	rsdlink 48tob.arg
	tmdsort -o k2tob2.tmd a.tmd
	cmplz k2tob2.tmd k2tob2.lz
	del a.tmd
	cd ..\..

k2.mot:
	hdlink /n /l k2.lis

