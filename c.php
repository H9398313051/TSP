
<?php
if (isset($_POST['execute'])) 
{
    // Replace 'python_script.py' with the actual name of your Python script file.
    exec('c ccode.c', $output, $return_value);

    if ($return_value === 0) {
        echo "c program executed successfully.";
    } else {
        echo "c program execution failed.";
    }
}
?>
