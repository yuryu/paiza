#! perl

use strict;
use warnings;
use Test::More;
use File::Slurp;
use FindBin;

my $PROG = "$FindBin::Bin/../paiza-ec";
my $TESTDIR = "$FindBin::Bin/01/";

opendir(my $dh, $TESTDIR);
ok $dh;
while(my $file = readdir($dh)) {
    next unless $file =~ /^test(.+)$/;
    my $p = $1;
    my $result = `$PROG < "$TESTDIR/$file"`;
    my $expected = read_file("$TESTDIR/ans$p");
    is $result, $expected;
}
closedir($dh);

done_testing;
