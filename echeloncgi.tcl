#!/usr/bin/tclsh
#echelon.tcl, text generator for echelon regression testing (21 oct 1999)
#
# ADMechelon-lagger project (ref: http://www.echelon.wiretapped.net/)
# most keywords from: http://www.attrition.org/attrition/keywords.html
# most phrases from: http://www.echelon.wiretapped.net/echelon.cgi
# tcl code by ADMcrack@adm.freelsd.net
#

# Keywords updated by Mixter (database version 3.05+ / Mar 2000)
# CGI formating by Mixter
# Everything else from the ADM Crew

# procedure "main" formats the output like a mail,
# procedure "write_cgi_output" formats that into a cgi script output...
# these functions are easy to understand and you're encouraged to modify them

proc write_cgi_output {} {
 global rand_seed main
 if {[file exists /dev/urandom] && [file readable /dev/urandom]} rand-urandom
 incr rand_seed [clock seconds]
 catch {puts stdout "Content-type: text/html\n\n<HTML><HEAD><TITLE>SIPRNET Archives</TITLE></HEAD><BODY><PRE>"}
 catch {puts stdout [subst $main]}
 catch {puts stdout "\n</PRE></BODY></HTML>"}
}

set main {
[header]
[of hello] [of {} {[one grif]}]
[of {} {\nFrom: [one addr]}][of {} {\nTo: [one addr]}]

 [one text]

 [one keywords][of ps]
}

regsub -all "\n" {
 Netsec, SILKWORTH, Vortex, amnesty, margaret, black program, distributed,
 jurisdiction, newsham, SIRE, warner amendment, blacklisted campaign,
 Fort George, NIST, National Infrasturcture Protection Center, IN-Q-IT, inqit,
 IN-Q-IT backdoor, NIPR, NCSC, Bin Laden, TFN, Trinoo, Denial Of Service, LawNet, SIPR,
 Waihopai, INFOSEC, Information Security, Information Warfare, IW, IS,
 Privacy, Information Terrorism, Terrorism Defensive Information, Defense
 Information Warfare, Offensive Information, Offensive Information Warfare,
 National Information Infrastructure, InfoSec, Reno, Compsec, Computer
 Terrorism, Firewalls, Secure Internet Connections, ISS, Passwords, DefCon V,
 Hackers, Encryption, Espionage, USDOJ, NSA, CIA, S/Key, SSL, FBI, Secert
 Service, USSS, Defcon, Military, White House, Undercover, NCCS, Mayfly, PGP,
 PEM, RSA, Perl-RSA, MSNBC, bet, AOL, AOL TOS, CIS, CBOT, AIMSX, STARLAN,
 3B2, BITNET, COSMOS, DATTA, E911, FCIC, HTCIA, IACIS, UT/RUS, JANET, JICC,
 ReMOB, LEETAC, UTU, VNET, BRLO, BZ, CANSLO, CBNRC, CIDA, KGB, BKA,
 Compsec, LLC, DERA, Mavricks, Meta-hackers, Steve Case, Telex,
 Military Intelligence, Scully, Flame, Infowar, Bubba, Freeh, Archives,
 Sundevil, jack, Investigation, ISACA, NCSA, spook words, Verisign, Secure,
 ASIO, Lebed, ICE, NRO, Lexis-Nexis, NSCT, SCIF, FLiR, Lacrosse, Flashbangs,
 HRT, DIA, USCOI, CID, BOP, FINCEN, FLETC, NIJ, ACC, AFSPC, BMDO, NAVWAN,
 NRL, RL, NAVWCWPNS, NSWC, USAFA, AHPCRC, ARPA, LABLINK, USACIL, USCG, NRC,
 CDC, DOE, FMS, HPCC, NTIS, SEL, USCODE, CISE, SIRC, CIM, ISN, DJC, SGC,
 UNCPCJ, CFC, DREO, CDA, DRA, SHAPE, SACLANT, BECCA, DCJFTF, HALO, HAHO, FKS,
 868, GCHQ, DITSA, SORT, AMEMB, NSG, HIC, EDI, SAS, SBS, UDT, GOE, DOE, GEO,
 Masuda, Forte, AT, GIGN, Exon Shell, CQB, CONUS, CTU, RCMP, GRU, SASR,
 GSG-9, 22nd SAS, GEOS, EADA, BBE, STEP, Echelon, Dictionary, MD2, MD4, MDA,
 MYK, MI5, MI6, 757, Kh-11, Shayet-13, SADMS, Spetznaz,
 Recce, CIO, NOCS, Halcon, Duress, RAID, Psyops, grom, D-11, SERT, VIP,
 ARC, S.E.T. Team, MP5k, DREC, DEVGRP, DF, DSD, FDM, GRU, LRTS, SIGDEV,
 NACSI, PSAC, PTT, RFI, SIGDASYS, TDM. SUKLO, SUSLO, TELINT, ELF,
 MF, VHF, UHF, SHF, SASP, WANK, Colonel, domestic disruption, smuggle, 15kg,
 nitrate, Pretoria, M-14, enigma, Bletchley Park, Clandestine, nkvd, argus,
 afsatcom, CQB, NVD, Counter Terrorism Security, Rapid Reaction, Corporate
 Security, Police, sniper, PPS, ASIS, ASLET, TSCM, Security Consulting, High
 Security, Security Evaluation, Electronic Surveillance, MI-17, IDS,
 Defense Satellite, Defense System, source code,  Counterterrorism,
 spies, eavesdropping, debugging, interception, COCOT, trojan, trojaned,
 rhost, rhosts, SETA, Amherst, Broadside, Capricorn, Gamma, Gorizont, Guppy,
 Ionosphere, Mole, Keyhole, Kilderkin, Artichoke, Badger, Cornflower, Daisy,
 Egret, Iris, Hollyhock, Jasmine, Juile, Vinnell, B.D.M.,Sphinx, Stephanie,
 Reflection, Spoke, Talent, Trump, FX, FXR, IMF, POCSAG, Covert Video,
 Competitor, EO, Chan, Alouette,executive, Event Security, Mace, Cap-Stun,
 stakeout, ninja, ASIS, ISA, EOD, Oscor, Merlin, NTT, SL-1, Rolm, TIE,
 Tie-fighter, PBX, SLI, NTT, MSCJ, MIT, 69, RIT, Time, MSEE, MIT Team,
 CSE, Embassy, ETA, Porno, Fax, finks, Fax encryption, white noise,
 pink noise, CRA, M.P.R.I., top secret, Mossberg, 50BMG, Macintosh Security,
 Protection, SIG, sweep, Medco, TRD, TDR, sweeping, TELINT, Audiotel, VIP,
 Harvard, 1080H, SWS, Asset, Satellite imagery, force, Cypherpunks,
 Coderpunks, TRW, remailers, replay, redheads, RX-7, explicit, FLAME,
 Pornstars, AVN, Playboy, Anonymous, Sex, chaining, codes, Nuclear,
 quiche, DES, NATIA, NATOA, sneakers, counterintelligence, industrial
 espionage, PI, TSCI, industrial intelligence, H.N.P., Juiliett Class
 Submarine, Locks, loch, Ingram Mac-10, sigvoice, ssa, E.O.D., SEMTEX,
 penrep, racal, OTP, OSS, Blowpipe, CCS, GSA, Kilo Class, squib, primacord,
 RSP, Becker, Nerd, fangs, Austin, Comirex, GPMG, Speakeasy, humint, GEODSS,
 SORO, M5, ANC, zone, SBI, DSS, S.A.I.C., Minox, Keyhole, SAR, Rand
 Corporation, Wackenhutt, EO, Wackendude, mol, Hillal, GGL, CTU, botux,
 Virii, CCC, Blacklisted 411, Internet Underground, XS4ALL, Retinal Fetish,
 TDYC, W3, CUD, CdC, Weekly World News, Zen, World Domination, Dead, GRU,
 M72750, Salsa, Blowfish, Gorelick, Glock, Ft. Meade, press-release,
 Indigo, wire transfer, e-cash, Bubba the Love Sponge, Digicash, zip, SWAT,
 Ortega, crypto-anarchy, AT&T, SGI, SUN, MCI, Blacknet, Middleman, KLM,
 Blackbird, plutonium, Texas, jihad, SDI, Uzi, Fort Meade, supercomputer,
 bullion, 3, Blackmednet, Propaganda, ABC, Satellite phones, Planet-1,
 cryptanalysis, nuclear, FBI, Panama, fissionable, Sears Tower, NORAD, Delta
 Force, SEAL, virtual, Dolch, secure shell, screws, Black-Ops, Area51, SABC,
 garbage, market, Stego, unclassified, utopia, orthodox, Alica, SHA,
 Global, gorilla, Bob, Pseudonyms, MITM, Gray Data, VLSI, mega, Leitrim,
 Yakima, Sugar Grove, Cowboy, Gist, 8182, Gatt, Platform, 1911, Geraldton,
 UKUSA, veggie, 3848, Morwenstow, Consul, Oratory, Pine Gap, Menwith, Mantis,
 DSD, BVD, 1984, Flintlock, cybercash, government, hate, speedbump,
 illuminati, president, freedom, cocaine, Roswell, ESN, COS, E.T., credit
 card, b9, fraud, assasinate, virus, anarchy, rogue, mailbomb, Chelsea,
 Whitewater, plutonium, BATF, SGDN, Nike, Atlas, Delta, TWA, Kiwi,
 Lynch, Pixar, IRIDF, eternity server, Skytel, Yukon, Templeton, Majestic
 LUK, Cohiba, Soros, Standford, niche, H&K, USP, sardine, bank, EUB,
 USP, PCS, NRO, Red Cell, Glock 26, snuffle, Patel, package, ISI, INR, INS,
 IRS, GRU, RUOP, GSS, NSP, SRI, Ronco, Armani, BOSS, Chobetsu, FBIS, BND,
 SISDE, FSB, BfV, IB, froglegs, JITEM, SADF, advise, TUSA, HoHoCon, SISMI,
 FIS, MSW, Spyderco, UOP, SSCI, NIMA, MOIS, SVR, SIN, advisors, SAP, OAU,
 312, NB, CBM, CTP, Sardine, SBIRS, SGDN, ADIU, DEADBEEF, IDP, IDF, Halibut,
 SONANGOL, Loin, EG&G, AIEWS, AMW, WORM, MP5K-SD, Tesla,
 WINGS, cdi, DynCorp, UXO, Ti, THAAD, package, chosen, PRIME, SURVIAC,
 MAGNUM, RHYOLITE, AQUACADE, CHALET, VORTEX, MERINO, KILTING, UMBRA, GAMMA,
 NOFORN, ORCON
} {} keywords
regsub -all {, } $keywords , keywords
set keywords [join [split $keywords ,] "\n"]

set grif {
 HUMINT report
 Surveillance
 DISA Official Announcement
 Message from Department of Defense
 NIPC Confidential
 For Your Eyes Only
 Classified
 Proprietary
 ""
 US Government
 Alert
 resistance
 No subject
 Re: No subject
 DDOS
 Not For Public Release
 National Security Action Memorandum
 NetSec newsletter
 Top Secret
 Secret
 Important
 UMBRA
 GAMMA Item
 NOFORN-ORCON
 Intelligence Report
}

set 1st_name {
 John Jefferson Mary Martin Joseph Brad Harry Al Donald Ron Russell Adam
 Frank Barry Edwin Michael Harry Richard David Joseph Ken Ronald Scott Chris
 James Victor Eric Glen Ramon Eugene Jane Antonio Jose Carlos Eduardo
 Larry Perry Tony Alan William John George Ivan Bob Arnold Frank Yosy Stevie
}

set 2nd_name {
 Smith Eriksson Knowles Clinton Reno Merritt Mixter Jones Brown Bulger
 Godwin Kopp Rudolph Webb Gerena Jean Johnson Lopez Levine White Castro
 Casserino Swedberg Benett Johnson Jackson Kelley Brotherton Stotts Hafich
 Perry Killer Williamson Keily Fritz Swartz Ivanov Igels Dickinson Richards
}

set 3rd_name {
 {} {} {} {} {} A. B. C. D. E. F. G. H. I. J. K. L. M. N. O. P. Q. R. S. T. U.
}

set lev1 {
 Colonel Lt General {Lieutenant Colonel} {Lt Colonel} Major
 Captain {General Brigadier} President Admiral
}

set lev2 {
 Director {Chief of Staff} {Deputy Director} Inspector Commander
 Seargant Private {Vice Commander} Ex-Commander
}

set dept {
 Security Awareness Division (M56)
 National Security Agency
 NSA NetSec
 Counterterrorism Initiative
 Computer Emergency Response Team
 US Defence Intelligence Agency
 Federal Bureau of Investigation
 Federal Emergency Management Agency
 National Infrastructure Protection Center
 Departament of Justice
 Intelligence and Security (IGIS)
 [rand 50 4]th Space Operations Squadron, USAF
 [rand 300 50]th Mission Support Squadron 
 [rand 300 50]th Space Group, USAF
 [rand 800 50]th Communications Squadron Commander, USAF
 Joint National Test Facility
 Joint Defence Space Research Facility 
 NSWC (Naval Surface Warfare Center, Dahlgren, VA)
 Office of the [of {Vice President} President] of the United States of America
 STRATCOM (US Strategic Command, Omaha, NE)
 TACCSF (Theater Air Command & Control Simulation Facility, Kirtland AFB, NM)
 Tactical Information Broadcasting Service (TIBS)/Tactical Receiver and Related Applications (TRAPS) Data Dissemination System (TDDS) (TIBS/TDDS)
 United States Joint Chiefs of Staff
 United States National Security Council
 HQ Consolidated Space Test Center (HQ CSTC)
}

set addr {
 [of lev1], [one dept]
 [of lev1] [of 1st_name] [of 3rd_name] [of 2nd_name], [of lev2], [one dept]
 [of lev1] [of 3rd_name] [of 2nd_name], [of lev2], [one dept]
 [of lev1] [of 1st_name] [of 3rd_name] [of 2nd_name], [one dept]
 [of lev1] of [of lev2], [one dept]
 [of lev2] of [one dept]
 [one dept]
}

set place {
 {New York} {Los Angeles} Washington Dallas Chicago Nurrungar
 {[of country]} {[of country]} {[of country]} Moscow suburbs {Fort Meade}
}

set when {
 on January 1st as that year 2000 thing really heats up
 next week
 in [rand 10 2] days
 tomorrow
 just as everybody's sitting down for [of {Christmas dinner} {thanksgiving}]
 in a couple of days time
 in the afternoon
 about [rand 20 4] hours
 soon
 next month
 this morning
 when you least expect it
 after the satellite has passed over
}

set time {
 last night
 this night
 this morning
 today
 yesterday
 last monday
 [rand 14 2] days ago
 [rand 4 1] months ago
}

set person {
 Ayman Al Zawahiri
 Usame bin Laden
 Khalfan Khamis Mohamed
 Xu Yongyue
 Al Amn al-Askari
 President
 Al Gore
}

set who {
 copycat Unabomber
 Cypherpunks
 Supreme Assembly of the Islamic Revolution in Iraq (SAIRI)
 members of the holy revolutionary front
 SIGINT from the KWT-46
 Teams up to date from the training facility
 DDoS
 islamic fundamentalists
 INFOSEC
 [one ss] guys
 [one ss] members
 [one person]'s people
}

set os {
 Windows NT
 Windows 2000
 Windows 98
 CISCO
 Cray UNICOS
 Linux
 AIX
 Chinese Linux
}

set net {
 SIRPNet
 ARPANET
 nasa.gov
 gchq.gov.uk
 *.gov
 *.mil
 NAVAL
 important
 high profile
}

set sigint {
 SIGINT COMINT ELINT RADINT LASINT
}

set thing {
 release approximately a kilogram of botulinum toxin into the water supply in [of place]
 press conference in [of place]
 to infiltrate the DIA facility in [of place] [one when]
 to pass the counterfeit notes to the [one ss] [of worker] working out of [of place]
 a meeting set up in [of place] [one when]
 released a manifesto [one when]
 to use the [one os] backdoor on some [one net] nodes
 to drive a tanker full of fertiliser and diesel across the border from Mexico
 to hijack a 747 out of [of place]
 meet up with the GSG-9 defectors in [of place] [one when]
 fly out to [of place] [one when]
 to get the layout of the M51 Physical Security Division into the diplomatic bag out of The White House [one when]
 to destroy [of sigint] capabilities operating in [of place] [one when]
 to wiretap the T1 coming out of the [one ss] in [of place] [one when]
 to get some Information Terrorism going, primarily from the [one ss] in [of place] [one when]
 to inflict minimal casualties on [one ss] personnel at [of place] [one when]
 bring the DF, ZARK, SERT, VIP, ARC and S.E.T
 to sell details of the updated AFIWC COMPUSEC plans to the [of place] diplomat in [of place] [one when]
 to hook-up with the [one ss] defector in hiding in [of place] [one when]
 broadcast this morning
 to start a crypto-anarchy jihad (holy war) on the [one ss] boys stationed in [of place] [one when]
 to break [one person] out of federal custody and get him to [of place] [one when]
 to hack into the Virtual Data Center (VDC) Network from an insecure dialin in [of place] [one when]
 to incite the masses [one thing]
 to create some domestic disruption [of place] [one when]
 to pass the [one what] to a [one ss] [of worker] stationed in [of place] [one when]
 to rob bank at [of place] [one time]
 to spread Sarin somewhere at [of place]'s metro
 lost [one what] somewhere in [of place] [one time]
 to kill [one person] as they pass through Washington after the satellite has passed over. 
 to sponsor development of new criptography algorithm
 to build quantum computers and break [of RSA DH] keys
 to use [one ss]'s [of DES IDEA RSA DH CAST] breaking machine
 to lauch Internet smurf attack against [one ss] [one when]
}

set what {
 documents
 important gears
 key codes
 [one grif] documents
 dangerous chemicals
 weapon papers
}

set do {
 They have
 There's a planned
 They're going
 Those damn [one who]
 We found plans on him about
 I heard they were going
 Theyve no choice other than
 You've got
}

set ss {
 Secret Service
 MOSSAD
 CIA
 DEA
 Siemens
 [one keyword]/[one keyword]
 MI-6
 DoD
 GRU
 [one keyword]
 Hezbollah
 DoJ
 Tactical Information Broadcasting Service
 [one who]
 850th Communications Squadron
 NSA
 BATF
 Spetznatz
}

set worker {
 commander agent defector informer officer guy {deep cover agent}
}

set threat {
 Finally, we got that info about [one ss], you will receive it [one when]
 As [one who], we must [one thing]
 A [one who] sent in a threat [one when] [one thing]
 Never underestimate the [one who] - they resolved [one thing]
 [one who] suggests that theyre being blackmailed
 [one do] [one thing]
 If we're to succed in halting the [one who] community, theres no better time than now [one thing] then [one thing]
 You should pay the [one ss] agent so he can get on with the job! He's got [one thing]
 The [one ss] boys are kidding themselves if they think they can get away with it
 The defector inside [one ss] cabled us [one when]
 The [of worker] in the [one ss] passed on some new information
 The [of worker] we have inside the [one ss] says they're planning [one thing]
 Gotta hand it to the [one ss] guys - turns out the group were going [one thing]
 [one person] plan [one thing]
 [one person] made broadcast [one time]. [one do] [one thing]
 [one person] just got picked up [one time] by our agents. 
 An [of country] diplomat is well positioned [one thing]
}

set country {
 Iraq Israel Cuba Afganistan Russia USA Germany France England Greece
 China Korea Italy Australia India Japan Pakistan
 Bahrain Iraq Kuwait Lebanon Libya Oman Qatar {Saudi Arabia}
 Syria {United Arab Emirates} Yemen UAE
}

set text {
 [upcase [one threat]].
 [upcase [one threat]]..
 [upcase [one threat]]. Further to that, [one text]
 [upcase [one threat]]. Additionally, [one text]
 [upcase [one threat]]. Also, [one text]
 [upcase [one threat]].\nbtw.\n[one text]
 [upcase [one threat]]. Finally, [one threat].
}

set ps {
 {[pgp]} {[pgp]} {[pgp]} {[pgp]} {[pgp]} {[pgp]} {} {} {} {} {} {} {\n} {\n\n}
 {[attachment]} {[attachment]} {[attachment]} {[attachment]} {[attachment]}
 {\nps. Don't keep this mail} {\nps. Do not go back to your house\n\n\n\n}
 {\nps. Did not reply to me back!} {\nps. Don't try to contact me\n\n}
 {\nNext keyword: [one keywords]} {\n\nDo not back to safehouse of course\n}
 {\t[of ORE WTP] [of 97 98 99]-100[rand 100 10][of X CX]}
}

set hello {
 {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {} {#[rand 999 99]th:\n}
 {See what I got [one time]:\n} {\n\n\n=====================================\n}
 {Sure, you will interested in this:\n\n------------------------------------\n}
 {That what i got from [one ss]:\n} {[of worker] sent me today:\n}
}

#MINSTD random generator (ref: ftp://ftp.inria.fr/prog/libraries/random.c.Z)

set rand_seed 1999
set rand_xor 0

proc rand {max {add 0}} {
global rand_seed rand_xor
 set hi [expr {$rand_seed / 127773}]
 set lo [expr {$rand_seed % 127773}]
 set rand_seed [set test [expr {16807 * $lo - 2836 * $hi}]]
 if {$test <= 0} {incr rand_seed 2147483647}
 set r [expr {($rand_seed % $max + $rand_seed / 65535) ^ $rand_xor}]
 return [expr {$add + ( $r % $max)}]
}

proc rand-urandom {} {
global rand_xor
 if {[catch {
  set f [open /dev/urandom r]
  scan [read $f 3] {%c%c%c} a b c
  close $f
  set rand_xor [expr {$a + ($b << 8) + ($c << 16)}]
 }]} {
  if {[info exists f]} {catch {close $f}}
 }
}

proc rep {s n} {
 for {set a {}} {$n} {incr n -1} {append a $s}
 return $a
}

proc rchar {s} {return [string index $s [rand [string length $s]]]}

set b64 ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/
set pgp_crc 0x0b704ce
proc base64 {args} {
global b64 pgp_crc
 set l 0
 foreach i $args {
  set i [expr {$i}]
  set pgp_crc [expr {$pgp_crc ^ ($i << 16)}]
  for {set j 0} {$j < 8} {incr j} {
   if {[set pgp_crc [expr {$pgp_crc << 1}]] & 0x1000000} {
    set pgp_crc [expr {$pgp_crc ^ 0x1864cfb}]
   }
  }
  append o [string index $b64 [
   switch [expr {$l % 3}] {
    0 {expr {$i >> 2}}
    1 {expr {(($p & 0x03) << 4) | (($i & 0xF0) >> 4)}}
    2 {expr {(($p & 0x0F) << 2) | (($i & 0xC0) >> 6)}}
   }
  ]]
  if {($l % 3) == 2} {append o [string index $b64 [expr {$i & 0x3F}]]}
  set p $i
  incr l
 }
 append o [switch [expr {$l % 3}] {
  1 {set a A==}
  2 {set a ==}
 }]
 return $o
}

proc pgp {} {
global b64 pgp_crc
 set pgp_crc 0x0b704ce
 append a "\n-----BEGIN PGP MESSAGE-----\n"
 append a "Version: 2.6.[rand 3 1]\n\n"
 set len [rand 1000 200]
 append a [base64 0x84 [rand 256] [rand 256]]
 for {set n 4} {$n < $len} {incr n 4} {
   if {!($n % 64)} {append a "\n"}
   append a [base64 [rand 256] [rand 256] [rand 256]]
 }
 set c1 [expr {($pgp_crc >> 16) & 255}]
 set c2 [expr {($pgp_crc >> 8) & 255}]
 set c3 [expr {($pgp_crc) & 255}]
 append a "\n=[base64 $c1 $c2 $c3]\n"
 append a "-----END PGP MESSAGE-----\n"
 return $a
}

set ksusp {
 blast hack attack takeover hijack kill frame track strike burn rape alert
 break report tracking info
}

set attach {
 {[of place]-[of ksusp]}
 {[one ss]} {[one ss]-[of ksusp]}
 {[one keywords]} {[one keywords]-[of ksusp]}
 {[of sigint]-[of ksusp]}
}

proc attachment {} {
 set f [of attach].[of arj ARJ zip ZIP tgz tar.gz tar.Z]
 set len [rand 1000 500]
 append b "\n--[rand 2147483647 214748364]-8[rand 99999999 10000000]-"
 append b "9[rand 99999999 10000000]=:$len\n"
 append a "\n$b"
 append a "Content-Type: TEXT/PLAIN; CHARSET=US-ASCII; NAME=\"$f\"\n"
 append a "Content-Transfer-Encoding: BASE64\n"
 append a "Content-Disposition: ATTACHMENT; FILENAME=\"$f\"\n"

 for {set n 0} {$n < $len} {incr n 4} {
   if {!($n % 76)} {append a "\n"}
   append a [base64 [rand 256] [rand 256] [rand 256]]
 }
 append a "$b"
}

set dom {mil MIL org ORG net com gov GOV}
set subject {
 Re: [one what]
 Re: [one ss]
 Re: [one keywords]
 [one keywords]
 [one ss] ALERT!
 [one dept] info
}

proc header {} {
 set td [clock format [clock seconds] -gmt 1 -format {%a, %d %b %Y %T +0000}]
 set tid [clock format [clock seconds] -gmt 1 -format {%Y%m%d%H%M}]
 regsub -all {[ ,&/]} [one keywords] {} f
 regsub -all {[ ,&/]} [one keywords] {} t
 foreach w [rep . [rand 3 1]] {append mf [base64 [rand 255] [rand 255] [rand 255]].[of dom]}
 foreach w [rep . [rand 3 1]] {append mt [base64 [rand 255] [rand 255] [rand 255]].[of dom]}
 set id [rchar ABCDEF][rep [rchar ABCDEF] 2]10[rand 900 100]
 set l [of localhost $mf [rand 174 24].[rand 255].[rand 255].[rand 254 1]]
 append a "Received: (from $f@$l) by $mf (8.[of 9 8 9].[rand 6]/8.8.[rand 9]) od $id for $t@$mt; $td\n"
 append a "Date: $td\n"
 append a "From: $f <$f@$mf>\n"
 append a "Message-Id: <$tid.$id@$mf>\n"
 append a "To: $t@$mt\n"
 append a "Subject: [one subject]\n"
}

proc one {array} {
 global $array
 set things [split [set $array] "\n"]
 set max [llength $things]
 if {$max == 2} {return (...)}
 set n [expr {[rand [expr {$max - 2}] 1]}]
 set a [string trimleft [subst [lindex $things $n]]]
 set $array [join [lreplace $things $n $n] "\n"]
 return $a
}

proc of {args} {
 set things [if {[llength $args] == 1} {global $args; set $args} {set args}]
 set max [llength $things]
 set x [lindex $things [expr {[rand $max]}]]
 return [string trim [subst $x] " "]
}

proc upcase {text} {
 return [string toupper [string index $text 0]][string range $text 1 end]
}

write_cgi_output

#end
