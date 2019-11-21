using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;


namespace MediaSdk.ProcessDuplicate.Client
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            
           
        }

      
       
        private void MainWindow_Loaded(object sender, RoutedEventArgs e)
        {
          //DesignerProperties.GetIsInDesignMode()
        }
 

        #region Overrides of Window

        /// <summary>Raises the <see cref="E:System.Windows.Window.Closing" /> event.</summary>
        /// <param name="e">A <see cref="T:System.ComponentModel.CancelEventArgs" /> that contains the event data.</param>
        protected override void OnClosing(CancelEventArgs e)
        {
            //pdm.End();
            base.OnClosing(e);
        }

        #endregion
    }
}
