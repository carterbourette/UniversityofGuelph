<?php

/**
 * transferSession
 * Transfer the get session to the next page through url param list.
 *
 * IN: $arr $_GET.
 * RETURN: (String) url list.
 *
 **/
function transferSession($arr) {
    $string = "";
    foreach ($arr as $key=>$value) {
        $string = $string . "&" . $key . '=' . $value;
    } return $string;
}

/**
 * writeTemp
 * Write to a temp file to transfer information.
 *
 * IN: (String) text to file.
 * RETURN: NONE.
 *
 **/
function writeTemp($txt, $noappend=null) {
    if ($noappend == null) {
        $myfile = fopen("info.txt", "a+") or die("Unable to create file!");
    } else {
        $myfile = fopen("info.txt", "w+") or die("Unable to create file!");
    }
    fwrite($myfile, $txt . "\n");
    fclose($myfile);
}


    //  Delegate by given parameters
    if (isset($_POST['userid']) || isset($_GET['userid'])) {
        if (isset($_POST['userid'])) {
            $userid = str_replace(' ', '', $_POST['userid']);
        } else {
            $userid = str_replace(' ', '', $_GET['userid']);
        }
    } else {
        $userid = False;
    }

    if (isset($_GET['view'])) {
        header("Location: view.php?" . transferSession($_GET));
    }

    if(isset($_GET['form'])) {
        switch ($_GET['form']) {
            case "login":
                header("Location: view.php?userid=".$userid);
                break;
            case "post":
                //  Write data to temp file
                writeTemp($_POST['stream'],1);
                writeTemp($_POST['message']);

                //  Call C post program
                exec("./post " . $_POST['userid'], $output, $status);

                foreach($output as $line)
                    echo $line;
                $path = "view.php?userid=$userid";
                echo "<form action=\"$path\" method=\"post\"><button>Back to Streams</button></form>";
                break;
            case "addremove":
                //  Write data needed by addauthor
                $usr = trim($_POST['username']," ");
                writeTemp($_POST['stream'],1);

                // call function to add or remove user...
                if (isset($_POST['remove']) && $_POST['remove'] == 1) {
                    exec("./addauthor -r " . $usr, $output, $status);
                } else {
                    exec("./addauthor " . $usr, $output, $status);
                }

                //  Print results
                foreach($output as $line)
                    echo $line;
                $path = "view.php?userid=$userid";
                echo "<form action=\"$path\" method=\"post\"><button>Back to Streams</button></form>";

                break;
            case "mark":
                exec("./caller.py mark" . $userid, $out, $status);
                foreach($out as $line) {
                    echo $line;
                }
                break;
            default:
                echo 'not defined ' . $_GET['form'];
        }
    } else {
        echo 'form to process';
        var_dump($_POST);
    }

 ?>
