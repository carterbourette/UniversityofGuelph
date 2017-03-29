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
#   readFile.pl
#      Author(s): Carter Bourette (0916638) & Mark Sansome (0916066)
#      Project: Lab Assignment 2 Task 2 Script
#      Date of Last Update: Monday, January 25, 2016.
#
#      Functional Summary
#         readFile.pl takes in a CSV (comma separated version) file 
#         and prints out the fields.  
#         There are three fields:
#            1. name
#            2. gender (F or M)
#            3. number of people with this name  
#
#         This code will also count the top 5 number of female and male
#         names in this file and print this out at the end.
#
#         The file represents the names of people in the population 
#         for a particular year of birth in the United States of America.  
#         Officially it is the "National Data on the relative frequency 
#         of given names in the population of U.S. births where the individual 
#         has a Social Security Number".
#
#      Commandline Parameters: 2
#         $ARGV[0] = name of the input file containing the names
#         $ARGV[1] = name of the input file containing the names
#
#      References
#         Name files from http://www.ssa.gov/OACT/babynames/limits.html
#

#
#   Variables to be used
#
my $EMPTY = q{};
my $SPACE = q{ };
my $COMMA = q{,};

my $filename     = $EMPTY;
my $classfilename= $EMPTY;
my @records;
my $record_count = -1;
my $classrecord_count = -1;
my $female_count = 0;
my $male_count   = 0;
my $female_count_top = 0;
my $male_count_top = 0;
my $found = 0;
my $missing = 0;
my $femalePos =0;
my $malePos =0;
my $firstMale = 0;
my @first_name;
my @gender;
my @number;
my @classfirst_name;
my $csv          = Text::CSV->new({ sep_char => $COMMA });

#
#   Check that you have the right number of parameters
#
if ($#ARGV != 1 ) {
   print "Usage: readFile.pl <names file>\n" or
      die "Print failure\n";
   exit;
} else {
    $filename = $ARGV[0];
    $classfilename = $ARGV[1];
    
}

#
#   Open the input file and load the contents into records array
#
open my $names_fh, '<', $filename
   or die "Unable to open names file: $filename\n";

@records = <$names_fh>;

close $names_fh or
   die "Unable to close: $ARGV[0]\n";   # Close the input file

#
#   Parse each line and store the information in arrays 
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
foreach my $name_record ( @records ) {
   if ( $csv->parse($name_record) ) {
      my @master_fields = $csv->fields();
      $record_count++;
       
      $first_name[$record_count] = $master_fields[0];
      $gender[$record_count]     = $master_fields[1];
       if ( $gender [$record_count] eq 'M' && $firstMale == 0){
           $firstMale = $record_count;
       }
      $number[$record_count]     = $master_fields[2];
   } else {
      warn "Line/record could not be parsed: $records[$record_count]\n";
   }
}

#
#   Open the input file and load the contents into records array
#
open $names_fh, '<', $classfilename
or die "Unable to open names file: $filename\n";

@records = <$names_fh>;

close $names_fh or
die "Unable to close: $ARGV[0]\n";   # Close the input file

#
#   Parse each line and store the information in arrays
#   representing each field
#
#   Extract each field from each name record as delimited by a comma
#
foreach my $name_record2 ( @records ) {
    if ( $csv->parse($name_record2) ) {
        my @master_fields = $csv->fields();
        $classrecord_count++;
        $classfirst_name[$classrecord_count] = $master_fields[0];
    } else {
        warn "Line/record could not be parsed: $records[$record_count]\n";
    }
}

#
#   Print out the records and counts
#
for my $i ( 0..$classrecord_count ) {
    for my $j ( 0..$record_count ) {
        if ( $classfirst_name[$i] eq $first_name[$j] ) {
            if ($gender[$j] eq 'F'){
                $femalePos = $j + 1;
            }
            if ($gender[$j] eq 'M') {
                $malePos = $j + 1 - $firstMale;
            }
        }
    }

    if ($femalePos != 0 && $malePos != 0){
        print $classfirst_name[$i] . " (",$femalePos. ", ". $malePos.")";
                    $found++;
    } elsif ($femalePos != 0 && $malePos == 0 ){
        print $classfirst_name[$i] . " (",$femalePos.")";
                    $found++;
    } elsif ($femalePos == 0 && $malePos != 0 ) {
        print $classfirst_name[$i] . " (",$malePos.")";
                    $found++;
    } else {
        print $classfirst_name[$i] . " (0)";
        $missing++;
    }
    print "\n";
    $femalePos=0;
    $malePos=0;
}

print "Number of found names: ",$found;
print "\n";
print "Number of missing names: ",$missing;
print "\n";

#
#   End of Script
#
