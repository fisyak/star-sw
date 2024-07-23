#! /bin/tcsh -f
mysql -h star-fc1.sdcc.bnl.gov --port=3336 -u "FC_user" --password=FCatalog FileCatalog_BNL -e 'select triggerSetupName from TriggerSetups where triggerSetupName like  "production%"  order by triggerSetupID;'| egrep -v '(test|setup|carl|scaler|no|triggerSetupName|Killer)'
