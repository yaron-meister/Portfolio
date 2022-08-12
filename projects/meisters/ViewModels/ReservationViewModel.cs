using GalaSoft.MvvmLight.Command;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Input;

namespace Meisters.ViewModels
{
    class ReservationViewModel : ViewModelBase
    {

        #region Commands

        public ICommand PrintCheckCommand => new RelayCommand(() =>
        {
            
        });

        public ICommand PayCommand => new RelayCommand(() =>
        {

        });

        public ICommand ExitCommand => new RelayCommand(() =>
        {

        });

        public ICommand SendCommand => new RelayCommand(() =>
        {

        });

        #endregion Commands
    }
}
