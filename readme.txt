This repository will contain notes, workarounds, instructions for building software on:
  $ uname -srm
  OSF1 V5.1 alpha

The system starts with vendor cc:

 $ which cc
 /usr/bin/cc

 $ cc -V
 Compaq C V6.5-303 (dtk) on HP Tru64 UNIX V5.1B (Rev. 2650)
 Compiler Driver V6.5-302 (dtk) cc Driver

 whichs work very well, and a cxx that is still being explored.

 By default it does not work:

 $ cat 1.cpp
 int main() { }

 $ cxx 1.cpp
 ld (prelink):
 Can't open: /usr/lib/cmplrs/cxx/V6.5-042/_main.o (No such file or directory)
 ld:
 Can't open: /usr/lib/cmplrs/cxx/V6.5-042/_main.o (No such file or directory)

But there is hope. There is _main.o elsewhere, the install source has it, and:

 $ cxx -oldcxx 1.cpp

 => success, probably good enough.

Also:
 $ cxx -c 1.cpp
 $ cxx -oldcxx 1.o
=> success

From here I have built, at least:
 tar (1.34)                           important to extract source
 make current release (4.3)           ?important for handling makefiles, esp. for out of tree builds?
   bootstrap first make 3.81?
 bash current release (5.1.8)         possibly important?
 gcc 3.4.6                            very useful? or try vendor cc more?; does not require gmp/mpfr/mpc; not much worse than 4.7.4?
 gcc 4.7.4                            latest gcc release that supports tru64
 tcl current release (8.6)            for running gcc tests eventually
 sed current release (4.8)            suspected would fix a problem but turned out not relevant
 m4 current release (1.4.18)          for eventual autoconf
 gawk current 5.1.0                   for gcc option parsing
 python 2.7                           for my own build scripts; configure -disable-ipv6
 xz current 5.2.5                     to decompress source (could be done on other hosts)
 gzip current 1.10                    to decompress source (could be done on other hosts? vendor works?)
 bzip2 current 1.0.8                  ditto?
 diff current 3.7                     some test harness seemed to fail with vendor diff
 gdb old 7.4                          (newer requires a more capable C++ compiler, this version was chosen "randomly" and work)
 iconv current 1.16                   wanted by something?
 gettext current 0.19.8.1             popular dependency? optional?
 gmp versions? 4.3.2 ?and? 6.2.1?     used by newer gcc
 mpfr versions? 2.4.2 ?and? 4.1.0?    used by newer gcc
 mpc version? 0.8.1 ?and? 1.2.1?      used by newer gcc
 libtool 2.4.6                        dependency of guile?
 nettle                               for eventual openssl/openssh
 pkgconfig                            wanted by something? (guile?) -with-internal-glib
 libunicodestring                     wanted by something? (guile?)
 grep current 3.6

 and more

CC=cc CFLAGS="-pthread -c99" are good parameters to configure for native cc.

CFLAGS=-pthread is good for gcc also
e.g. otherwise:
$HOME/s/pkg-config-0.29.1/glib/glib/deprecated/gthread.h:133:3: error: unknown type name 'pthread_mutex_t'
$HOME/s/pkg-config-0.29.1/glib/glib/deprecated/gthread.h:163:5: error: unknown type name 'pthread_t'

After initially groveling for various source, apt-get source was settled upon
as a good source for source.

It is important to note that tar and make are important for bootstrapping.
Vendor tar can often not extract source and vendor make can often not build it.
As well, it is advised when using vendor make, do not do out-of-tree builds. 

$ ls bin lib

bin:
2to3                              gettext.sh                        python2-config
alphaev67-dec-osf5.1-c++          gettextize                        python2.7
alphaev67-dec-osf5.1-g++          grep                              python2.7-config
alphaev67-dec-osf5.1-gcc          gunzip                            recode-sr-latin
alphaev67-dec-osf5.1-gcc-3.4.6    gzexe                             rftp
alphaev67-dec-osf5.1b-c++         gzip                              rlogin-cwd
alphaev67-dec-osf5.1b-g++         iconv                             runtest
alphaev67-dec-osf5.1b-gcc         idle                              sdiff
alphaev67-dec-osf5.1b-gcc-4.7.4   info                              sed
alphaev67-dec-osf5.1b-gcc-ar      install-info                      sexp-conv
alphaev67-dec-osf5.1b-gcc-nm      kibitz                            smtpd.py
alphaev67-dec-osf5.1b-gcc-ranlib  libtool                           sqlite3_analyzer
autoexpect                        libtoolize                        tar
autopasswd                        lpunlock                          tclsh8.6
autopoint                         lzcat                             texi2any
awk                               lzcmp                             texi2dvi
bash                              lzdiff                            texi2pdf
bashbug                           lzegrep                           texindex
bunzip2                           lzfgrep                           timed-read
bzcat                             lzgrep                            timed-run
bzcmp                             lzless                            tknewsbiff
bzdiff                            lzma                              tkpasswd
bzegrep                           lzmadec                           unbuffer
bzfgrep                           lzmainfo                          uncompress
bzgrep                            lzmore                            unlzma
bzip2                             m4                                unxz
bzip2recover                      make                              unzip
bzless                            makeinfo                          unzipsfx
bzmore                            mkpasswd                          weather
c++                               msgattrib                         xgettext
cmp                               msgcat                            xkibitz
cpp                               msgcmp                            xpstat
cryptdir                          msgcomm                           xz
decryptdir                        msgconv                           xzcat
dejagnu                           msgen                             xzcmp
diff                              msgexec                           xzdec
diff3                             msgfilter                         xzdiff
dislocate                         msgfmt                            xzegrep
egrep                             msggrep                           xzfgrep
envsubst                          msginit                           xzgrep
expect                            msgmerge                          xzless
fgrep                             msgunfmt                          xzmore
ftp-rfc                           msguniq                           zcat
funzip                            multixterm                        zcmp
g++                               nettle-hash                       zdiff
gawk                              nettle-lfib-stream                zegrep
gawk-5.1.0                        nettle-pbkdf2                     zfgrep
gcc                               ngettext                          zforce
gcc-ar                            passmass                          zgrep
gcc-nm                            pdftexi2dvi                       zipgrep
gcc-ranlib                        pod2texi                          zipinfo
gccbug                            pydoc                             zless
gcov                              python                            zmore
gdb                               python-config                     znew
gettext                           python2

lib:
bash                       libgettextpo.so.0          libitm.so.1                libssp.a
charset.alias              libgettextpo.so.5.5.4      libitm.so.1.0.0            libssp.so
expect5.45.4               libgettextsrc-0.19.8.1.so  libitm.spec                libssp.so.0
gawk                       libgettextsrc.la           libltdl.a                  libssp.so.0.0.0
gcc                        libgettextsrc.so           libltdl.la                 libssp_nonshared.a
gettext                    libgmp.a                   libltdl.so                 libstdc++.a
itcl4.2.1                  libgmp.la                  libltdl.so.10.3.1          libstdc++.so
libasprintf.a              libgmp.so                  libltdl.so.7               libstdc++.so.6
libasprintf.la             libgmp.so.10               liblzma.a                  libstdc++.so.6.0.17
libasprintf.so             libgmp.so.14.4.1           liblzma.so                 libstdc++.so.6.0.3
libasprintf.so.0           libgomp.a                  liblzma.so.5               libstdc++.so.6.0.3-gdb.py
libasprintf.so.0.0.0       libgomp.so                 liblzma.so.7.2.5           libsupc++.a
libbfd.a                   libgomp.so.1               libmpc.a                   libtcl8.6.so
libbz2.a                   libgomp.so.1.0.0           libmpc.la                  libtclstub8.6.a
libcharset.a               libgomp.spec               libmpc.so                  pkgconfig
libcharset.la              libiberty.a                libmpc.so.2                python2.7
libcharset.so              libiconv.la                libmpc.so.2.0.0            sqlite3.34.0
libcharset.so.1            libiconv.so                libmpc.so.3                tcl8
libcharset.so.1.0.0        libiconv.so.2              libmpc.so.5.2.1            tcl8.6
libgcc_s.so                libiconv.so.8.6.1          libmpfr.a                  tclConfig.sh
libgcc_s.so.1              libintl.a                  libmpfr.la                 tclooConfig.sh
libgettextlib-0.19.8.1.so  libintl.la                 libmpfr.so                 tdbc1.1.2
libgettextlib.la           libintl.so                 libmpfr.so.6               tdbcmysql1.1.2
libgettextlib.so           libintl.so.8               libmpfr.so.7.1.0           tdbcodbc1.1.2
libgettextpo.a             libintl.so.9.1.5           libnettle.a                tdbcpostgres1.1.2
libgettextpo.la            libitm.a                   libopcodes.a               texinfo
libgettextpo.so            libitm.so                  libpython2.7.a             thread2.8.6

However:

 - Good notes were not taken along the way.
 - Perhaps some mistakes were made (use configure -disable-shared? Use prefix != $HOME?)
 - Native cc was underused?
   Native cc was used to build alphaev67-dec-osf5.1-gcc-3.4.6 and was optional thereafter.

The system also started with:
  /usr/local/bin/wget

However this wget fails to work with https, which many sites mandate.

And scp is broken.

Therefore file transfer so far has been:
 wget to a newer system then:
 ssh x <file "cat>file"

The eventual goal is a modern gcc, preferably master, but 10.x as a compromise.

Challenges and work remains:

 - Finish getting Python3 working.
 - Gcc 11.x requires a C++11 compiler.
 - Gcc 4.7 is the last release with Tru64 support.
 - Gcc 4.8 is the first C++11 compiler.
 - Binutils is supported or not?
 - gnutls
 - openssl
 - ssh
 - wget
 - git (difficult)
 - guile
 - expect
 - Use native cc/cxx more and report patches upstream.
 - cmake (requires fairly new C++)

So the present situation is perhaps: no host, no target, no cross build.

But it remains to be seen:
 - If binutils has support, then cross build becomes easy.
 - Adding support to binutils would make future bootstraps easier.
 - Without binutils support, we likely have to patch gcc 4.8 at a minimum.
 - Support was removed in gcc 4.8.
