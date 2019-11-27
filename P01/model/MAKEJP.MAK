ANM_DIR=..\anm
TIM_DIR=..\tim
NAME=..\..\name
NAMEVS=..\..\namevs
JAPAN_DIR=japan\rsd
JPTOB_DIR=jptob\rsd

all : jp.mot jp1.mod jp2.mod
    psymake

jp1.mod: $(JAPAN_DIR)\jp1.lz $(JPTOB_DIR)\jptob1.lz
	hdlink /n /l jp1.lis

$(JAPAN_DIR)\jp1.lz:
	cd $(JAPAN_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 481
	timpos $(TIM_DIR)/mune.tim    404   0   0 483
	timpos $(TIM_DIR)/hara1.tim   404  96  48 482
	timpos $(TIM_DIR)/hara3.tim   448  96  80 482
	timpos $(TIM_DIR)/hara2.tim   448 176  64 482
	timpos $(TIM_DIR)/tuno.tim    492 128   0 480
	timpos $(TIM_DIR)/me.tim      502   0 112 482
	timpos $(TIM_DIR)/head.tim    512   0  16 482
	timpos $(TIM_DIR)/hige.tim    512 112 128 482
	timpos $(TIM_DIR)/headura.tim 512 136  32 482
	timpos $(TIM_DIR)/syokaku.tim 534 136  96 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	rsdlink jpnomal.arg
	tmdsort -o jp1.tmd a.tmd
	cmplz jp1.tmd jp1.lz
	del a.tmd
	cd ..\..

$(JPTOB_DIR)\jptob1.lz:
	cd $(JPTOB_DIR)
	timpos $(TIM_DIR)/body.tim    320   0   0 481
	timpos $(TIM_DIR)/mune.tim    404   0   0 483
	timpos $(TIM_DIR)/hara1.tim   404  96  48 482
	timpos $(TIM_DIR)/hara3.tim   448  96  80 482
	timpos $(TIM_DIR)/hara2.tim   448 176  64 482
	timpos $(TIM_DIR)/tuno.tim    492 128   0 480
	timpos $(TIM_DIR)/me.tim      502   0 112 482
	timpos $(TIM_DIR)/head.tim    512   0  16 482
	timpos $(TIM_DIR)/hige.tim    512 112 128 482
	timpos $(TIM_DIR)/headura.tim 512 136  32 482
	timpos $(TIM_DIR)/syokaku.tim 534 136  96 482
	timpos $(TIM_DIR)/hane2.tim   534 192 144 482
	timpos $(TIM_DIR)/hara4.tim   556   0 160 482
	timpos $(TIM_DIR)/hane1.tim   558 192 176 482
	timpos $(TIM_DIR)/kage.tim    492   0   0 482
	timpos $(NAME)/name1.tim      896   0   0 487
	timpos $(NAMEVS)/namevs1.tim  896  16  16 487
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name1.tim      name.lz
	cmplz $(NAMEVS)/namevs1.tim  namevs.lz
	hdlink /n /l ..\..\jp1t.lis
	rsdlink jptob.arg
	tmdsort -o jptob1.tmd a.tmd
	cmplz jptob1.tmd jptob1.lz
	del a.tmd
	cd ..\..

jp2.mod: $(JAPAN_DIR)\jp2.lz $(JPTOB_DIR)\jptob2.lz
	hdlink /n /l jp2.lis

$(JAPAN_DIR)\jp2.lz:
	cd $(JAPAN_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 489
	timpos $(TIM_DIR)/mune.tim    660   0   0 491
	timpos $(TIM_DIR)/hara1.tim   660  96  48 490
	timpos $(TIM_DIR)/hara3.tim   704  96  80 490
	timpos $(TIM_DIR)/hara2.tim   704 176  64 490
	timpos $(TIM_DIR)/tuno.tim    748 128   0 488
	timpos $(TIM_DIR)/me.tim      758   0 112 490
	timpos $(TIM_DIR)/head.tim    768   0  16 490
	timpos $(TIM_DIR)/hige.tim    768 112 128 490
	timpos $(TIM_DIR)/headura.tim 768 136  32 490
	timpos $(TIM_DIR)/syokaku.tim 790 136  96 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	rsdlink jpnomal.arg
	tmdsort -o jp2.tmd a.tmd
	cmplz jp2.tmd jp2.lz
	del a.tmd
	cd ..\..

$(JPTOB_DIR)\jptob2.lz:
	cd $(JPTOB_DIR)
	timpos $(TIM_DIR)/body.tim    576   0   0 489
	timpos $(TIM_DIR)/mune.tim    660   0   0 491
	timpos $(TIM_DIR)/hara1.tim   660  96  48 490
	timpos $(TIM_DIR)/hara3.tim   704  96  80 490
	timpos $(TIM_DIR)/hara2.tim   704 176  64 490
	timpos $(TIM_DIR)/tuno.tim    748 128   0 488
	timpos $(TIM_DIR)/me.tim      758   0 112 490
	timpos $(TIM_DIR)/head.tim    768   0  16 490
	timpos $(TIM_DIR)/hige.tim    768 112 128 490
	timpos $(TIM_DIR)/headura.tim 768 136  32 490
	timpos $(TIM_DIR)/syokaku.tim 790 136  96 490
	timpos $(TIM_DIR)/hane2.tim   790 192 144 490
	timpos $(TIM_DIR)/hara4.tim   812   0 160 490
	timpos $(TIM_DIR)/hane1.tim   814 192 176 490
	timpos $(TIM_DIR)/kage.tim    748   0   0 490
	timpos $(NAME)/name1.tim      926   0   0 495
	timpos $(NAMEVS)/namevs1.tim  896  56  16 495
	cmplz $(TIM_DIR)/body.tim    body.lz
	cmplz $(TIM_DIR)/headura.tim headura.lz
	cmplz $(TIM_DIR)/tuno.tim    tuno.lz
	cmplz $(TIM_DIR)/syokaku.tim syokaku.lz
	cmplz $(TIM_DIR)/hara1.tim   hara1.lz
	cmplz $(TIM_DIR)/mune.tim    mune.lz
	cmplz $(TIM_DIR)/head.tim    head.lz
	cmplz $(TIM_DIR)/hara3.tim   hara3.lz
	cmplz $(TIM_DIR)/hige.tim    hige.lz
	cmplz $(TIM_DIR)/me.tim      me.lz
	cmplz $(TIM_DIR)/hara2.tim   hara2.lz
	cmplz $(TIM_DIR)/hane2.tim   hane2.lz
	cmplz $(TIM_DIR)/hara4.tim   hara4.lz
	cmplz $(TIM_DIR)/hane1.tim   hane1.lz
	cmplz $(TIM_DIR)/kage.tim    kage.lz
	cmplz $(NAME)/name1.tim      name.lz
	cmplz $(NAMEVS)/namevs1.tim  namevs.lz
	hdlink /n /l ..\..\jp2t.lis
	rsdlink jptob.arg
	tmdsort -o jptob2.tmd a.tmd
	cmplz jptob2.tmd jptob2.lz
	del a.tmd
	cd ..\..

jp.mot: $(JAPAN_DIR)\$(ANM_DIR)/jpiki.lz \
		$(JPTOB_DIR)\$(ANM_DIR)/jptob0.lz \
		$(JPTOB_DIR)\$(ANM_DIR)/jptob1.lz \
		$(JPTOB_DIR)\$(ANM_DIR)/kbttob0.lz \
		$(JPTOB_DIR)\$(ANM_DIR)/kbttob1.lz \
		$(JPTOB_DIR)\$(ANM_DIR)/kbttob2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpido0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpido1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg3.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg4.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpdmg5.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpkgk0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jpkgk1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jphri0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jphri1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jptki0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/jptki1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb0m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb1m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neocmb2m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neokgk1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/neokgk2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb0m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb1m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03cmb2m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03gek1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/03gek2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb0m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb1m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22cmb2m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22gek1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/22gek2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb0m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb1m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cmb2m.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/ttkn.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/ngrr0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/ngrr1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/sasi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/tos0.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/tos1.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/tos2.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/bkstp.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/cyg.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/hrdkn.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/mynr0s.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/mynr1s.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/l_sasi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/l_nage.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2uke.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2dmg.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2dmgk.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2dmg47.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2dmg24.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2dmg26.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/a2puru.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/hyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/kwhyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/hmhyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/47hyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/54hyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/tnhyoi.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/hm_jp.lz \
		$(JAPAN_DIR)\$(ANM_DIR)/hm_my.lz
	hdlink /n /l jp.lis

$(JAPAN_DIR)\$(ANM_DIR)/jpiki.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jpiki
	cmplz jpiki.mtn jpiki.lz
	cd ..\..

$(JPTOB_DIR)\$(ANM_DIR)/jptob0.lz:
	cd $(JPTOB_DIR)\$(ANM_DIR)
	bin2mtn jptob0
	cmplz jptob0.mtn jptob0.lz
	cd ..\..

$(JPTOB_DIR)\$(ANM_DIR)/jptob1.lz:
	cd $(JPTOB_DIR)\$(ANM_DIR)
	bin2mtn jptob1
	cmplz jptob1.mtn jptob1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn dmg0
	cmplz dmg0.mtn jpdmg0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn dmg1
	cmplz dmg1.mtn jpdmg1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpido0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jpido0
	cmplz jpido0.mtn jpido0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpido1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jpido1
	cmplz jpido1.mtn jpido1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn kbsdmg2a
	cmplz kbsdmg2a.mtn jpdmg2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg3.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn kbsdmg3a
	cmplz kbsdmg3a.mtn jpdmg3.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg4.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn kbsdmg2b
	cmplz kbsdmg2b.mtn jpdmg4.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpdmg5.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn kbsdmg3b
	cmplz kbsdmg3b.mtn jpdmg5.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpkgk0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jpkgk0
	cmplz jpkgk0.mtn jpkgk0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jpkgk1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jpkgk1
	cmplz jpkgk1.mtn jpkgk1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jphri0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jphri0
	cmplz jphri0.mtn jphri0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jphri1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jphri1
	cmplz jphri1.mtn jphri1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jptki0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jptki0
	cmplz jptki0.mtn jptki0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/jptki1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn jptki1
	cmplz jptki1.mtn jptki1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb0
	cmplz cmb0.mtn cmb0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb0m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb0m
	cmplz cmb0m.mtn cmb0m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb1
	cmplz cmb1.mtn cmb1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb1m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb1m
	cmplz cmb1m.mtn cmb1m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb2
	cmplz cmb2.mtn cmb2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cmb2m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cmb2m
	cmplz cmb2m.mtn cmb2m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/ttkn.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn ttkn
	cmplz ttkn.mtn ttkn.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/ngrr0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn ngrr0
	cmplz ngrr0.mtn ngrr0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/ngrr1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn ngrr1
	cmplz ngrr1.mtn ngrr1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/sasi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn sasi
	cmplz sasi.mtn sasi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/tos0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn tos0
	cmplz tos0.mtn tos0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/tos1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn tos1
	cmplz tos1.mtn tos1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/tos2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn tos2
	cmplz tos2.mtn tos2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/bkstp.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn bkstp
	cmplz bkstp.mtn bkstp.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/cyg.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn cyg
	cmplz cyg.mtn cyg.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/hrdkn.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn hrdkn
	cmplz hrdkn.mtn hrdkn.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/mynr0s.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn mynr0s
	cmplz mynr0s.mtn mynr0s.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/mynr1s.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn mynr1s
	cmplz mynr1s.mtn mynr1s.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/l_sasi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn l_sasi
	cmplz l_sasi.mtn l_sasi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/l_nage.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn l_nage
	cmplz l_nage.mtn l_nage.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/hm_jp.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn hm_jp
	cmplz hm_jp.mtn hm_jp.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/hm_my.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn hm_my
	cmplz hm_my.mtn hm_my.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2uke.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2uke
	cmplz a2uke.mtn a2uke.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2dmg.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2dmg
	cmplz a2dmg.mtn a2dmg.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2dmgk.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2dmgk
	cmplz a2dmgk.mtn a2dmgk.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2dmg47.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2dmg47
	cmplz a2dmg47.mtn a2dmg47.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2dmg24.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2dmg24
	cmplz a2dmg24.mtn a2dmg24.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2dmg26.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2dmg26
	cmplz a2dmg26.mtn a2dmg26.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/a2puru.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn a2puru
	cmplz a2puru.mtn a2puru.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/hyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn hyoi
	cmplz hyoi.mtn hyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/kwhyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn kwhyoi
	cmplz kwhyoi.mtn kwhyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/hmhyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn hmhyoi
	cmplz hmhyoi.mtn hmhyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/47hyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 47hyoi
	cmplz 47hyoi.mtn 47hyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/54hyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 54hyoi
	cmplz 54hyoi.mtn 54hyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/tnhyoi.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn tnhyoi
	cmplz tnhyoi.mtn tnhyoi.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb0
	cmplz neocmb0.mtn neocmb0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb0m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb0m
	cmplz neocmb0m.mtn neocmb0m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb1
	cmplz neocmb1.mtn neocmb1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb1m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb1m
	cmplz neocmb1m.mtn neocmb1m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb2
	cmplz neocmb2.mtn neocmb2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neocmb2m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neocmb2m
	cmplz neocmb2m.mtn neocmb2m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neokgk1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neokgk1
	cmplz neokgk1.mtn neokgk1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/neokgk2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn neokgk2
	cmplz neokgk2.mtn neokgk2.lz
	cd ..\..

$(JPTOB_DIR)\$(ANM_DIR)/kbttob0.lz:
	cd $(JPTOB_DIR)\$(ANM_DIR)
	bin2mtn kbttob0
	cmplz kbttob0.mtn kbttob0.lz
	cd ..\..

$(JPTOB_DIR)\$(ANM_DIR)/kbttob1.lz:
	cd $(JPTOB_DIR)\$(ANM_DIR)
	bin2mtn kbttob1
	cmplz kbttob1.mtn kbttob1.lz
	cd ..\..

$(JPTOB_DIR)\$(ANM_DIR)/kbttob2.lz:
	cd $(JPTOB_DIR)\$(ANM_DIR)
	bin2mtn kbttob2
	cmplz kbttob2.mtn kbttob2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb0
	cmplz 03cmb0.mtn 03cmb0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb0m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb0m
	cmplz 03cmb0m.mtn 03cmb0m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb1
	cmplz 03cmb1.mtn 03cmb1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb1m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb1m
	cmplz 03cmb1m.mtn 03cmb1m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb2
	cmplz 03cmb2.mtn 03cmb2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03cmb2m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03cmb2m
	cmplz 03cmb2m.mtn 03cmb2m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03gek1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03gek1
	cmplz 03gek1.mtn 03gek1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/03gek2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 03gek2
	cmplz 03gek2.mtn 03gek2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb0.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb0
	cmplz 22cmb0.mtn 22cmb0.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb0m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb0m
	cmplz 22cmb0m.mtn 22cmb0m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb1
	cmplz 22cmb1.mtn 22cmb1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb1m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb1m
	cmplz 22cmb1m.mtn 22cmb1m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb2
	cmplz 22cmb2.mtn 22cmb2.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22cmb2m.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22cmb2m
	cmplz 22cmb2m.mtn 22cmb2m.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22gek1.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22gek1
	cmplz 22gek1.mtn 22gek1.lz
	cd ..\..

$(JAPAN_DIR)\$(ANM_DIR)/22gek2.lz:
	cd $(JAPAN_DIR)\$(ANM_DIR)
	bin2mtn 22gek2
	cmplz 22gek2.mtn 22gek2.lz
	cd ..\..


