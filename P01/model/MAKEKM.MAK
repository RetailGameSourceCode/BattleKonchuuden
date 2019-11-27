ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
RSD_DIR=47\rsd
RSDTOB_DIR=47tob\rsd

all : km.mot km1.mod km2.mod
    psymake

km1.mod: $(RSD_DIR)\km1.lz $(RSDTOB_DIR)\kmtob1.lz
	hdlink /n /l km1.lis

$(RSD_DIR)\km1.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/doutai.tim  448   0  16 482
	timpos $(TIM_DIR)/body.tim    448 128  32 482
	timpos $(TIM_DIR)/hara2.tim   464   0  48 482
	timpos $(TIM_DIR)/hara1.tim   480   0 128 482
	timpos $(TIM_DIR)/hane.tim    464 128  64 482
	timpos $(TIM_DIR)/me.tim      512   0   0 480
	timpos $(TIM_DIR)/head.tim    480 192  96 482
	timpos $(TIM_DIR)/skin.tim    496 128 112 482
	timpos $(TIM_DIR)/skin2.tim   496 192 160 482
	timpos $(TIM_DIR)/skin3.tim   504 192 144 482
	rsdlink 47km.arg
	tmdsort -o km1.tmd a.tmd
	cmplz km1.tmd km1.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\kmtob1.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/doutai.tim  448   0  16 482
	timpos $(TIM_DIR)/body.tim    448 128  32 482
	timpos $(TIM_DIR)/hara2.tim   464   0  48 482
	timpos $(TIM_DIR)/hara1.tim   480   0 128 482
	timpos $(TIM_DIR)/hane.tim    464 128  64 482
	timpos $(TIM_DIR)/head.tim    480 192  96 482
	timpos $(TIM_DIR)/skin.tim    496 128 112 482
	timpos $(TIM_DIR)/skin2.tim   496 192 160 482
	timpos $(TIM_DIR)/skin3.tim   504 192 144 482
	timpos $(TIM_DIR)/me.tim      512   0   0 480
	timpos $(TIM_DIR)/hane1.tim   512  64 176 482
	timpos $(TIM_DIR)/hane2.tim   512 128 192 482
	timpos $(TIM_DIR)/hane3.tim   512 192 208 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name47.tim     896   0   0 487
	timpos $(NAMEVS)/namevs47.tim 896  16  16 487
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/skin2.tim   skin2.lz
	cmplz $(TIM_DIR)/skin3.tim   skin3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane3.tim   hane3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name47.tim     name.lz
	cmplz $(NAMEVS)/namevs47.tim namevs.lz
	hdlink /n /l ..\..\km1t.lis
	rsdlink 47hn.arg
	tmdsort -o kmtob1.tmd a.tmd
	cmplz kmtob1.tmd kmtob1.lz
	del a.tmd
	cd ..\..

km2.mod: $(RSD_DIR)\km2.lz $(RSDTOB_DIR)\kmtob2.lz
	hdlink /n /l km2.lis

$(RSD_DIR)\km2.lz:
	cd $(RSD_DIR)
	timpos $(TIM_DIR)/doutai.tim  704   0  16 490
	timpos $(TIM_DIR)/body.tim    704 128  32 490
	timpos $(TIM_DIR)/hara2.tim   720   0  48 490
	timpos $(TIM_DIR)/hara1.tim   736   0 128 490
	timpos $(TIM_DIR)/hane.tim    720 128  64 490
	timpos $(TIM_DIR)/me.tim      768   0   0 488
	timpos $(TIM_DIR)/head.tim    736 192  96 490
	timpos $(TIM_DIR)/skin.tim    752 128 112 490
	timpos $(TIM_DIR)/skin2.tim   752 192 160 490
	timpos $(TIM_DIR)/skin3.tim   760 192 144 490
	rsdlink 47km.arg
	tmdsort -o km2.tmd a.tmd
	cmplz km2.tmd km2.lz
	del a.tmd
	cd ..\..

$(RSDTOB_DIR)\kmtob2.lz:
	cd $(RSDTOB_DIR)
	timpos $(TIM_DIR)/doutai.tim  704   0  16 490
	timpos $(TIM_DIR)/body.tim    704 128  32 490
	timpos $(TIM_DIR)/hara2.tim   720   0  48 490
	timpos $(TIM_DIR)/hara1.tim   736   0 128 490
	timpos $(TIM_DIR)/hane.tim    720 128  64 490
	timpos $(TIM_DIR)/head.tim    736 192  96 490
	timpos $(TIM_DIR)/skin.tim    752 128 112 490
	timpos $(TIM_DIR)/skin2.tim   752 192 160 490
	timpos $(TIM_DIR)/skin3.tim   760 192 144 490
	timpos $(TIM_DIR)/me.tim      768   0   0 488
	timpos $(TIM_DIR)/hane1.tim   768  64 176 490
	timpos $(TIM_DIR)/hane2.tim   768 128 192 490
	timpos $(TIM_DIR)/hane3.tim   768 192 208 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name47.tim     926   0   0 495
	timpos $(NAMEVS)/namevs47.tim 896  56  16 495
	cmplz $(TIM_DIR)/doutai.tim  doutai.lz
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/hane.tim    hane.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/skin.tim    skin.lz
	cmplz $(TIM_DIR)/skin2.tim   skin2.lz
	cmplz $(TIM_DIR)/skin3.tim   skin3.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hane3.tim   hane3.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name47.tim     name.lz
	cmplz $(NAMEVS)/namevs47.tim namevs.lz
	hdlink /n /l ..\..\km2t.lis
	rsdlink 47hn.arg
	tmdsort -o kmtob2.tmd a.tmd
	cmplz kmtob2.tmd kmtob2.lz
	del a.tmd
	cd ..\..

km.mot: $(RSD_DIR)\$(ANM_DIR)/47iki.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb0.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb1.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb2.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb0m.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb1m.lz \
		$(RSD_DIR)\$(ANM_DIR)/cmb2m.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg0.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg0m.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg1.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg1m.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg2.lz \
		$(RSD_DIR)\$(ANM_DIR)/47dmg2m.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki0.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki0m.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki1.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki1m.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki2.lz \
		$(RSD_DIR)\$(ANM_DIR)/geki2m.lz \
		$(RSD_DIR)\$(ANM_DIR)/jp_470s.lz \
		$(RSD_DIR)\$(ANM_DIR)/jp_471s.lz \
		$(RSD_DIR)\$(ANM_DIR)/hr_470s.lz \
		$(RSD_DIR)\$(ANM_DIR)/my_470s.lz \
		$(RSD_DIR)\$(ANM_DIR)/47ido0.lz \
		$(RSD_DIR)\$(ANM_DIR)/47ido1.lz \
		$(RSD_DIR)\$(ANM_DIR)/47sdmg.lz \
		$(RSD_DIR)\$(ANM_DIR)/47cyg.lz \
		$(RSD_DIR)\$(ANM_DIR)/47uke.lz \
		$(RSD_DIR)\$(ANM_DIR)/47rnb.lz \
		$(RSD_DIR)\$(ANM_DIR)/47sasi.lz \
		$(RSD_DIR)\$(ANM_DIR)/47ple.lz \
		$(RSD_DIR)\$(ANM_DIR)/47ftb0.lz \
		$(RSD_DIR)\$(ANM_DIR)/47ftb1.lz \
		$(RSDTOB_DIR)\$(ANM_DIR)/47tos0.lz \
		$(RSDTOB_DIR)\$(ANM_DIR)/47tos1.lz \
		$(RSDTOB_DIR)\$(ANM_DIR)/47tos2.lz \
		$(RSDTOB_DIR)\$(ANM_DIR)/47bkstp.lz
	hdlink /n /l km.lis

$(RSD_DIR)\$(ANM_DIR)/47iki.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47iki
	cmplz 47iki.mtn 47iki.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb0.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb0
	cmplz cmb0.mtn cmb0.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb1.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb1
	cmplz cmb1.mtn cmb1.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb2.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb2
	cmplz cmb2.mtn cmb2.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb0m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb0m
	cmplz cmb0m.mtn cmb0m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb1m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb1m
	cmplz cmb1m.mtn cmb1m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/cmb2m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn cmb2m
	cmplz cmb2m.mtn cmb2m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg0.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg0
	cmplz 47dmg0.mtn 47dmg0.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg0m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg0m
	cmplz 47dmg0m.mtn 47dmg0m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg1.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg1
	cmplz 47dmg1.mtn 47dmg1.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg1m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg1m
	cmplz 47dmg1m.mtn 47dmg1m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg2.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg2
	cmplz 47dmg2.mtn 47dmg2.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47dmg2m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47dmg2m
	cmplz 47dmg2m.mtn 47dmg2m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki0.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki0
	cmplz geki0.mtn geki0.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki0m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki0m
	cmplz geki0m.mtn geki0m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki1.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki1
	cmplz geki1.mtn geki1.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki1m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki1m
	cmplz geki1m.mtn geki1m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki2.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki2
	cmplz geki2.mtn geki2.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/geki2m.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn geki2m
	cmplz geki2m.mtn geki2m.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/jp_470s.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn jp_470s
	cmplz jp_470s.mtn jp_470s.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/jp_471s.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn jp_471s
	cmplz jp_471s.mtn jp_471s.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/hr_470s.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn hr_470s
	cmplz hr_470s.mtn hr_470s.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/my_470s.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn my_470s
	cmplz my_470s.mtn my_470s.lz
	cd ..\..

$(RSDTOB_DIR)\$(ANM_DIR)/47bkstp.lz:
	cd $(RSDTOB_DIR)\$(ANM_DIR)
	bin2mtn 47bkstp
	cmplz 47bkstp.mtn 47bkstp.lz
	cd ..\..

$(RSDTOB_DIR)\$(ANM_DIR)/47tos0.lz:
	cd $(RSDTOB_DIR)\$(ANM_DIR)
	bin2mtn 47tos0
	cmplz 47tos0.mtn 47tos0.lz
	cd ..\..

$(RSDTOB_DIR)\$(ANM_DIR)/47tos1.lz:
	cd $(RSDTOB_DIR)\$(ANM_DIR)
	bin2mtn 47tos1
	cmplz 47tos1.mtn 47tos1.lz
	cd ..\..

$(RSDTOB_DIR)\$(ANM_DIR)/47tos2.lz:
	cd $(RSDTOB_DIR)\$(ANM_DIR)
	bin2mtn 47tos2
	cmplz 47tos2.mtn 47tos2.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47ido0.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47ido0
	cmplz 47ido0.mtn 47ido0.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47ido1.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47ido1
	cmplz 47ido1.mtn 47ido1.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47sdmg.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47sdmg
	cmplz 47sdmg.mtn 47sdmg.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47cyg.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47cyg
	cmplz 47cyg.mtn 47cyg.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47uke.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47uke
	cmplz 47uke.mtn 47uke.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47rnb.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47rnb
	cmplz 47rnb.mtn 47rnb.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47sasi.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47sasi
	cmplz 47sasi.mtn 47sasi.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47ple.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47ple
	cmplz 47ple.mtn 47ple.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47ftb0.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47ftb0
	cmplz 47ftb0.mtn 47ftb0.lz
	cd ..\..

$(RSD_DIR)\$(ANM_DIR)/47ftb1.lz:
	cd $(RSD_DIR)\$(ANM_DIR)
	bin2mtn 47ftb1
	cmplz 47ftb1.mtn 47ftb1.lz
	cd ..\..

