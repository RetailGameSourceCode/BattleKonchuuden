ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
OSIKI_DIR=osiki\rsd
OSTOBI_DIR=ostobi\rsd

all : os.mot os1.mod os2.mod
    psymake

os1.mod: $(OSIKI_DIR)\os1.lz $(OSTOBI_DIR)\ostobi1.lz
	hdlink /n /l os1.lis

$(OSIKI_DIR)\os1.lz:
	cd $(OSIKI_DIR)
	timpos $(TIM_DIR)/hmse.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      378   0  48 482
	timpos $(TIM_DIR)/hm01.tim    384   0  80 482
	timpos $(TIM_DIR)/hara4.tim   384 152   0 481
	timpos $(TIM_DIR)/hmkao.tim   428 152  96 482
	timpos $(TIM_DIR)/hara3.tim   448   0  64 482
	timpos $(TIM_DIR)/hane1.tim   448 192 112 482
	timpos $(TIM_DIR)/hane2.tim   464   0 128 482
	timpos $(TIM_DIR)/hara1.tim   464  56  32 482
	timpos $(TIM_DIR)/hara2.tim   512   0   0 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink hmiki.arg
	tmdsort -o os1.tmd a.tmd
	cmplz os1.tmd os1.lz
	del a.tmd
	cd ..\..

$(OSTOBI_DIR)\ostobi1.lz:
	cd $(OSTOBI_DIR)
	timpos $(TIM_DIR)/hmse.tim    320   0  16 482
	timpos $(TIM_DIR)/me.tim      378   0  48 482
	timpos $(TIM_DIR)/hm01.tim    384   0  80 482
	timpos $(TIM_DIR)/hara4.tim   384 152   0 481
	timpos $(TIM_DIR)/hmkao.tim   428 152  96 482
	timpos $(TIM_DIR)/hara3.tim   448   0  64 482
	timpos $(TIM_DIR)/hane1.tim   448 192 112 482
	timpos $(TIM_DIR)/hane2.tim   464   0 128 482
	timpos $(TIM_DIR)/hara1.tim   464  56  32 482
	timpos $(TIM_DIR)/hara2.tim   512   0   0 480
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name27.tim     896   0   0 487
	timpos $(NAMEVS)/namevs27.tim 896  16  16 487
	cmplz $(TIM_DIR)/hmse.tim    hmse.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hm01.tim    hm01.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hmkao.tim   hmkao.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name27.tim     name.lz
	cmplz $(NAMEVS)/namevs27.tim namevs.lz
	hdlink /n /l ..\..\os1t.lis
	rsdlink hmtobi.arg
	tmdsort -o ostobi1.tmd a.tmd
	cmplz ostobi1.tmd ostobi1.lz
	del a.tmd
	cd ..\..

os2.mod: $(OSIKI_DIR)\os2.lz $(OSTOBI_DIR)\ostobi2.lz
	hdlink /n /l os2.lis

$(OSIKI_DIR)\os2.lz:
	cd $(OSIKI_DIR)
	timpos $(TIM_DIR)/hmse.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      634   0  48 490
	timpos $(TIM_DIR)/hm01.tim    640   0  80 490
	timpos $(TIM_DIR)/hara4.tim   640 152   0 489
	timpos $(TIM_DIR)/hmkao.tim   684 152  96 490
	timpos $(TIM_DIR)/hara3.tim   704   0  64 490
	timpos $(TIM_DIR)/hane1.tim   704 192 112 490
	timpos $(TIM_DIR)/hane2.tim   720   0 128 490
	timpos $(TIM_DIR)/hara1.tim   720  56  32 490
	timpos $(TIM_DIR)/hara2.tim   768   0   0 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink hmiki.arg
	tmdsort -o os2.tmd a.tmd
	cmplz os2.tmd os2.lz
	del a.tmd
	cd ..\..

$(OSTOBI_DIR)\ostobi2.lz:
	cd $(OSTOBI_DIR)
	timpos $(TIM_DIR)/hmse.tim    576   0  16 490
	timpos $(TIM_DIR)/me.tim      634   0  48 490
	timpos $(TIM_DIR)/hm01.tim    640   0  80 490
	timpos $(TIM_DIR)/hara4.tim   640 152   0 489
	timpos $(TIM_DIR)/hmkao.tim   684 152  96 490
	timpos $(TIM_DIR)/hara3.tim   704   0  64 490
	timpos $(TIM_DIR)/hane1.tim   704 192 112 490
	timpos $(TIM_DIR)/hane2.tim   720   0 128 490
	timpos $(TIM_DIR)/hara1.tim   720  56  32 490
	timpos $(TIM_DIR)/hara2.tim   768   0   0 488
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name27.tim     926   0   0 495
	timpos $(NAMEVS)/namevs27.tim 896  56  16 495
	cmplz $(TIM_DIR)/hmse.tim    hmse.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hm01.tim    hm01.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hmkao.tim   hmkao.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name27.tim     name.lz
	cmplz $(NAMEVS)/namevs27.tim namevs.lz
	hdlink /n /l ..\..\os2t.lis
	rsdlink hmtobi.arg
	tmdsort -o ostobi2.tmd a.tmd
	cmplz ostobi2.tmd ostobi2.lz
	del a.tmd
	cd ..\..

os.mot: $(OSIKI_DIR)\$(ANM_DIR)/osiki.lz \
		$(OSTOBI_DIR)\$(ANM_DIR)/ostob0.lz \
		$(OSTOBI_DIR)\$(ANM_DIR)/ostob1.lz
	hdlink /n /l os.lis

$(OSIKI_DIR)\$(ANM_DIR)/osiki.lz:
	cd $(OSIKI_DIR)\$(ANM_DIR)
	bin2mtn hm
	cmplz hm.mtn osiki.lz
	cd ..\..

$(OSTOBI_DIR)\$(ANM_DIR)/ostob0.lz:
	cd $(OSTOBI_DIR)\$(ANM_DIR)
	bin2mtn hmtob0
	cmplz hmtob0.mtn ostob0.lz
	cd ..\..

$(OSTOBI_DIR)\$(ANM_DIR)/ostob1.lz:
	cd $(OSTOBI_DIR)\$(ANM_DIR)
	bin2mtn hmtob1
	cmplz hmtob1.mtn ostob1.lz
	cd ..\..


