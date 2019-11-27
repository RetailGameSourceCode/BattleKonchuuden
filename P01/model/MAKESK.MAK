ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
SIROKAMI_DIR=51\rsd
SKTOB_DIR=51tob\rsd

all : sk.mot sk1.mod sk2.mod
    psymake

sk1.mod: $(SIROKAMI_DIR)\sk1.lz $(SKTOB_DIR)\sktob1.lz
	hdlink /n /l sk1.lis

$(SIROKAMI_DIR)\sk1.lz:
	cd $(SIROKAMI_DIR)
	timpos $(TIM_DIR)/body.tim    448   0  16 482
	timpos $(TIM_DIR)/hara.tim    448 128  32 482
	timpos $(TIM_DIR)/face.tim    448 224  48 482
	timpos $(TIM_DIR)/mune.tim    464 128  64 482
	timpos $(TIM_DIR)/me.tim      464 192  80 482
	timpos $(TIM_DIR)/kiba.tim    480   0  96 482
	timpos $(TIM_DIR)/faces.tim   480  32 112 482
	timpos $(TIM_DIR)/head.tim    480 128 128 482
	timpos $(TIM_DIR)/neck.tim    480 192 144 482
	rsdlink 51.arg
	tmdsort -o sk1.tmd a.tmd
	cmplz sk1.tmd sk1.lz
	del a.tmd
	cd ..\..

$(SKTOB_DIR)\sktob1.lz:
	cd $(SKTOB_DIR)
	timpos $(TIM_DIR)/body.tim    448   0  16 482
	timpos $(TIM_DIR)/hara.tim    448 128  32 482
	timpos $(TIM_DIR)/face.tim    448 224  48 482
	timpos $(TIM_DIR)/mune.tim    464 128  64 482
	timpos $(TIM_DIR)/me.tim      464 192  80 482
	timpos $(TIM_DIR)/kiba.tim    480   0  96 482
	timpos $(TIM_DIR)/faces.tim   480  32 112 482
	timpos $(TIM_DIR)/head.tim    480 128 128 482
	timpos $(TIM_DIR)/neck.tim    480 192 144 482
	timpos $(TIM_DIR)/hane1.tim   496 128 160 482
	timpos $(TIM_DIR)/hara4.tim   512   0 176 482
	timpos $(TIM_DIR)/hane2.tim   512 192 192 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name51.tim     896   0   0 487
	timpos $(NAMEVS)/namevs51.tim 896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kiba.tim    kiba.lz
	cmplz $(TIM_DIR)/faces.tim   faces.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/neck.tim    neck.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name51.tim     name.lz
	cmplz $(NAMEVS)/namevs51.tim namevs.lz
	hdlink /n /l ..\..\sk1t.lis
	rsdlink 51tob.arg
	tmdsort -o sktob1.tmd a.tmd
	cmplz sktob1.tmd sktob1.lz
	del a.tmd
	cd ..\..

sk2.mod: $(SIROKAMI_DIR)\sk2.lz $(SKTOB_DIR)\sktob2.lz
	hdlink /n /l sk2.lis

$(SIROKAMI_DIR)\sk2.lz:
	cd $(SIROKAMI_DIR)
	timpos $(TIM_DIR)/body.tim    704   0  16 490
	timpos $(TIM_DIR)/hara.tim    704 128  32 490
	timpos $(TIM_DIR)/face.tim    704 224  48 490
	timpos $(TIM_DIR)/mune.tim    720 128  64 490
	timpos $(TIM_DIR)/me.tim      720 192  80 490
	timpos $(TIM_DIR)/kiba.tim    736   0  96 490
	timpos $(TIM_DIR)/faces.tim   736  32 112 490
	timpos $(TIM_DIR)/head.tim    736 128 128 490
	timpos $(TIM_DIR)/neck.tim    736 192 144 490
	rsdlink 51.arg
	tmdsort -o sk2.tmd a.tmd
	cmplz sk2.tmd sk2.lz
	del a.tmd
	cd ..\..

$(SKTOB_DIR)\sktob2.lz:
	cd $(SKTOB_DIR)
	timpos $(TIM_DIR)/body.tim    704   0  16 490
	timpos $(TIM_DIR)/hara.tim    704 128  32 490
	timpos $(TIM_DIR)/face.tim    704 224  48 490
	timpos $(TIM_DIR)/mune.tim    720 128  64 490
	timpos $(TIM_DIR)/me.tim      720 192  80 490
	timpos $(TIM_DIR)/kiba.tim    736   0  96 490
	timpos $(TIM_DIR)/faces.tim   736  32 112 490
	timpos $(TIM_DIR)/head.tim    736 128 128 490
	timpos $(TIM_DIR)/neck.tim    736 192 144 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(TIM_DIR)/hane1.tim   752 128 160 490
	timpos $(TIM_DIR)/hara4.tim   768   0 176 490
	timpos $(TIM_DIR)/hane2.tim   768 192 192 490
	timpos $(NAME)/name51.tim     926   0   0 495
	timpos $(NAMEVS)/namevs51.tim 896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/hara.tim    hara.lz
	cmplz $(TIM_DIR)/face.tim    face.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/kiba.tim    kiba.lz
	cmplz $(TIM_DIR)/faces.tim   faces.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/neck.tim    neck.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name51.tim     name.lz
	cmplz $(NAMEVS)/namevs51.tim namevs.lz
	hdlink /n /l ..\..\sk2t.lis
	rsdlink 51tob.arg
	tmdsort -o sktob2.tmd a.tmd
	cmplz sktob2.tmd sktob2.lz
	del a.tmd
	cd ..\..

sk.mot: $(SIROKAMI_DIR)\$(ANM_DIR)/skiki.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51atc1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51atc2.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con0.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con0m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con1m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con2.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51con2m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg0.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg0m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg1m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg2.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg2m.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/01_51.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/02_51.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/32_510s.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/ngrr.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51bkstp.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51hyoi.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51ido0.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51ido1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51sdmg.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51tob0.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51tob1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51tob2.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/a2dmg51.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51ftb0.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51ftb1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51chag.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51ngrr1.lz \
		$(SIROKAMI_DIR)\$(ANM_DIR)/51uke.lz
	hdlink /n /l sk.lis

$(SIROKAMI_DIR)\$(ANM_DIR)/skiki.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51
	cmplz 51.mtn skiki.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg0.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg0
	cmplz 51dmg0.mtn 51dmg0.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg0m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg0m
	cmplz 51dmg0m.mtn 51dmg0m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg1
	cmplz 51dmg1.mtn 51dmg1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg1m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg1m
	cmplz 51dmg1m.mtn 51dmg1m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg2.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg2
	cmplz 51dmg2.mtn 51dmg2.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51dmg2m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51dmg2m
	cmplz 51dmg2m.mtn 51dmg2m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/01_51.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 01_51
	cmplz 01_51.mtn 01_51.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/02_51.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 02_51
	cmplz 02_51.mtn 02_51.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51bkstp.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51bkstp
	cmplz 51bkstp.mtn 51bkstp.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51hyoi.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51hyoi
	cmplz 51hyoi.mtn 51hyoi.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51ido0.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51ido0
	cmplz 51ido0.mtn 51ido0.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51ido1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51ido1
	cmplz 51ido1.mtn 51ido1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51sdmg.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51sdmg
	cmplz 51sdmg.mtn 51sdmg.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51tob0.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51tob0
	cmplz 51tob0.mtn 51tob0.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51tob1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51tob1
	cmplz 51tob1.mtn 51tob1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51tob2.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51tob2
	cmplz 51tob2.mtn 51tob2.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51uke.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51uke
	cmplz 51uke.mtn 51uke.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con0.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con0
	cmplz 51con0.mtn 51con0.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con0m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con0m
	cmplz 51con0m.mtn 51con0m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con1
	cmplz 51con1.mtn 51con1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con1m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con1m
	cmplz 51con1m.mtn 51con1m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con2.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con2
	cmplz 51con2.mtn 51con2.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51con2m.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51con2m
	cmplz 51con2m.mtn 51con2m.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51atc1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51atc1
	cmplz 51atc1.mtn 51atc1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51atc2.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51atc2
	cmplz 51atc2.mtn 51atc2.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/32_510s.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 32_510s
	cmplz 32_510s.mtn 32_510s.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/ngrr.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn ngrr
	cmplz ngrr.mtn ngrr.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/a2dmg51.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn a2dmg51
	cmplz a2dmg51.mtn a2dmg51.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51ftb0.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51ftb0
	cmplz 51ftb0.mtn 51ftb0.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51ftb1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51ftb1
	cmplz 51ftb1.mtn 51ftb1.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51chag.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51chag
	cmplz 51chag.mtn 51chag.lz
	cd ..\..

$(SIROKAMI_DIR)\$(ANM_DIR)/51ngrr1.lz:
	cd $(SIROKAMI_DIR)\$(ANM_DIR)
	bin2mtn 51ngrr1
	cmplz 51ngrr1.mtn 51ngrr1.lz
	cd ..\..


