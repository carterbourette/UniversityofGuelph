#!/usr/bin/perl
#
#   Packages and modules
#
use strict;
use warnings;
use version;   our $VERSION = qv('5.16.0');   # This is the version of Perl to be used
use Text::CSV  1.32;   # We will be using the CSV module (version 1.32 or higher)
                       # to parse each line

#
#   readStats.pl
#      Author(s): Carter Bourette (0916638) & Mark Sansome (0916066)
#      Project: Lab Assignment 4 Task 2 Script 
#      Date of Last Update: Saturday, February 8 2016.
#
#      Functional Summary
#         readStats.pl takes in a CSV (comma separated version) file 
#         containing death stats for the USA for a particular year
#
#      Commandline Parameters: 1
#         $ARGV[0] = name of the input file
#
#      References
#

#
#   Variables to be used
#
my $EMPTY = q{};
my $COMMA = q{,};
my $LIMIT = 5;

my $filename     = $EMPTY;
my $csv          = Text::CSV->new({ sep_char => $COMMA });
my @records;
my @female = (0,0,0,0,0,0,0,0,0,0,0,0);
my @male = (0,0,0,0,0,0,0,0,0,0,0,0);
my $record_count = 0;
my $deathCode;
my $deathName;


sub getMonth {
    my $arrVal = $_[0];
    if ($arrVal == 1){
        return "01/January";
    } elsif ($arrVal == 2) {
        return "02/February";
    }elsif ($arrVal == 3) {
        return "03/March";
    }elsif ($arrVal == 4) {
        return "04/April";
    }elsif ($arrVal == 5) {
        return "05/May";
    }elsif ($arrVal == 6) {
        return "06/June";
    }elsif ($arrVal == 7) {
        return "07/July";
    }elsif ($arrVal == 8) {
        return "08/August";
    }elsif ($arrVal == 9) {
        return "09/September";
    }elsif ($arrVal == 10) {
         return "10/October";
    }elsif ($arrVal == 11) {
        return "11/November";
    }elsif ($arrVal == 12) {
        return "12/December";
    }
}


#
#   Check that you have the right number of parameters
#
if ($#ARGV != 2 ) {
   print "Usage: readStats.pl <input csv file> <death code> <death name>\n" or
      die "Print failure\n";
   exit;
} else {
   $filename = $ARGV[0];
    $deathCode = $ARGV[1];
    $deathName = $ARGV[2];
}

#
#   Open the input file and load the contents into records array
#
open my $names_fh, '<', $filename
   or die "Unable to open names file: $filename\n";

@records = <$names_fh>;

close $names_fh or
   die "Unable to close: $ARGV[0]\n";   # Close the input file

print "\"Sex\",\"Month\",\"".$deathName."\"\n";

#
#   Parse each line and print out the information
#
foreach my $name_record ( @records ) {
   if ( $csv->parse($name_record) ) {
       my @master_fields = $csv->fields();
       if ($master_fields[12] eq $deathCode){
           if($master_fields[4] eq 'F'){
               $female[$master_fields[1] - 1] += 1;
           }
           else{
               $male[$master_fields[1] - 1] += 1;
           }
       }
       
   }
      $record_count++;
}

my $monthName;
my $count = 1;

foreach my $month (@female){
    $monthName = getMonth($count);
    print "Female,".$monthName.",".$month;
    print "\n";
    $count++;
}

$count = 1;

foreach my $month (@male){
    $monthName = getMonth($count);
    print "Male,".$monthName.",".$month;
    print "\n";
    $count++;
}

#
#   End of Script
#
