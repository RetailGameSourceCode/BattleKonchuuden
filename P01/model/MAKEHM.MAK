ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
HANA_DIR=hmiki\rsd
HMTOB_DIR=hmtobi\rsd

all : hm.mot hm1.mod hm2.mod
    psymake

hm1.mod: $(HANA_DIR)\hm1.lz $(HMTOB_DIR)\hmtob1.lz
	hdlink /n /l hm1.lis

$(HANA_DIR)\hm1.lz:
	cd $(HANA_DIR)
	timpos $(TIM_DIR)/hmse.tim    320   0  16 482
	timpos $(TIM_DIR)/hm01.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   430   0  32 482
	timpos $(TIM_DIR)/hmkao.tim   430 160  64 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/hara2.tim   448  80   0 480
	timpos $(TIM_DIR)/me.tim      486  80  80 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink hmiki.arg
	tmdsort -o hm1.tmd a.tmd
	cmplz hm1.tmd hm1.lz
	del a.tmd
	cd ..\..

$(HMTOB_DIR)\hmtob1.lz:
	cd $(HMTOB_DIR)
	timpos $(TIM_DIR)/hmse.tim    320   0  16 482
	timpos $(TIM_DIR)/hm01.tim    384   0  48 482
	timpos $(TIM_DIR)/hara1.tim   430   0  32 482
	timpos $(TIM_DIR)/hmkao.tim   430 160  64 482
	timpos $(TIM_DIR)/hara4.tim   448   0   0 481
	timpos $(TIM_DIR)/hara2.tim   448  80   0 480
	timpos $(TIM_DIR)/me.tim      486  80  80 482
	timpos $(TIM_DIR)/hane2.tim   384 152  96 482
	timpos $(TIM_DIR)/hane1.tim   408 152 112 482
	timpos $(TIM_DIR)/hara3.tim   512   0 128 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name26.tim     896   0   0 487
	timpos $(NAMEVS)/namevs26.tim 896  16  16 487
	cmplz $(TIM_DIR)/hmse.tim    hmse.lz
	cmplz $(TIM_DIR)/hm01.tim    hm01.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hmkao.tim   hmkao.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name26.tim     name.lz
	cmplz $(NAMEVS)/namevs26.tim namevs.lz
	hdlink /n /l ..\..\hm1t.lis
	rsdlink hmtobi.arg
	tmdsort -o hmtob1.tmd a.tmd
	cmplz hmtob1.tmd hmtob1.lz
	del a.tmd
	cd ..\..

hm2.mod: $(HANA_DIR)\hm2.lz $(HMTOB_DIR)\hmtob2.lz
	hdlink /n /l hm2.lis

$(HANA_DIR)\hm2.lz:
	cd $(HANA_DIR)
	timpos $(TIM_DIR)/hmse.tim    576   0  16 490
	timpos $(TIM_DIR)/hm01.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   686   0  32 490
	timpos $(TIM_DIR)/hmkao.tim   686 160  64 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/hara2.tim   704  80   0 488
	timpos $(TIM_DIR)/me.tim      742  80  80 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink hmiki.arg
	tmdsort -o hm2.tmd a.tmd
	cmplz hm2.tmd hm2.lz
	del a.tmd
	cd ..\..

$(HMTOB_DIR)\hmtob2.lz:
	cd $(HMTOB_DIR)
	timpos $(TIM_DIR)/hmse.tim    576   0  16 490
	timpos $(TIM_DIR)/hm01.tim    640   0  48 490
	timpos $(TIM_DIR)/hara1.tim   686   0  32 490
	timpos $(TIM_DIR)/hmkao.tim   686 160  64 490
	timpos $(TIM_DIR)/hara4.tim   704   0   0 489
	timpos $(TIM_DIR)/hara2.tim   704  80   0 488
	timpos $(TIM_DIR)/me.tim      742  80  80 490
	timpos $(TIM_DIR)/hane2.tim   640 152  96 490
	timpos $(TIM_DIR)/hane1.tim   664 152 112 490
	timpos $(TIM_DIR)/hara3.tim   768   0 128 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name26.tim     926   0   0 495
	timpos $(NAMEVS)/namevs26.tim 896  56  16 495
	cmplz $(TIM_DIR)/hmse.tim    hmse.lz
	cmplz $(TIM_DIR)/hm01.tim    hm01.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hmkao.tim   hmkao.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name26.tim     name.lz
	cmplz $(NAMEVS)/namevs26.tim namevs.lz
	hdlink /n /l ..\..\hm2t.lis
	rsdlink hmtobi.arg
	tmdsort -o hmtob2.tmd a.tmd
	cmplz hmtob2.tmd hmtob2.lz
	del a.tmd
	cd ..\..

hm.mot: $(HANA_DIR)\$(ANM_DIR)/hmiki.lz \
		$(HMTOB_DIR)\$(ANM_DIR)/hmtob0.lz \
		$(HMTOB_DIR)\$(ANM_DIR)/hmtob1.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom0.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom0m.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom1.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom1m.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom2.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcom2m.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmcha.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmido0.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmido1.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmatc1.lz \
		$(HANA_DIR)\$(ANM_DIR)/hmatc2.lz \
		$(HANA_DIR)\$(ANM_DIR)/25bkstp.lz
	hdlink /n /l hm.lis

$(HANA_DIR)\$(ANM_DIR)/hmiki.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hm
	cmplz hm.mtn hmiki.lz
	cd ..\..

$(HMTOB_DIR)\$(ANM_DIR)/hmtob0.lz:
	cd $(HMTOB_DIR)\$(ANM_DIR)
	bin2mtn hmtob0
	cmplz hmtob0.mtn hmtob0.lz
	cd ..\..

$(HMTOB_DIR)\$(ANM_DIR)/hmtob1.lz:
	cd $(HMTOB_DIR)\$(ANM_DIR)
	bin2mtn hmtob1
	cmplz hmtob1.mtn hmtob1.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom0.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom0
	cmplz hmcom0.mtn hmcom0.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom0m.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom0m
	cmplz hmcom0m.mtn hmcom0m.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom1.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom1
	cmplz hmcom1.mtn hmcom1.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom1m.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom1m
	cmplz hmcom1m.mtn hmcom1m.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom2.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom2
	cmplz hmcom2.mtn hmcom2.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcom2m.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcom2m
	cmplz hmcom2m.mtn hmcom2m.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmcha.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmcha
	cmplz hmcha.mtn hmcha.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmido0.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmido0
	cmplz hmido0.mtn hmido0.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmido1.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmido1
	cmplz hmido1.mtn hmido1.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmatc1.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmatc1
	cmplz hmatc1.mtn hmatc1.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/hmatc2.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn hmatc2
	cmplz hmatc2.mtn hmatc2.lz
	cd ..\..

$(HANA_DIR)\$(ANM_DIR)/25bkstp.lz:
	cd $(HANA_DIR)\$(ANM_DIR)
	bin2mtn 25bkstp
	cmplz 25bkstp.mtn 25bkstp.lz
	cd ..\..


