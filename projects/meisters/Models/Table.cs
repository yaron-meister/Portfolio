using Meisters.Services;
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Meisters.Models
{
    public enum ETableStatus
    {
        Clear,
        NoOrder,
        Order,
        Check
    }

    public class Table : Observable
    {
        private ETableStatus _status = ETableStatus.Clear;
        private uint _dinersNum;
        private Stopwatch _totalStopwatch = new Stopwatch();
        private Stopwatch _statusStopwatch = new Stopwatch();

        public Table(int id)
        {
            ID = id;
        }

        public int ID { get; }

        public ETableStatus Status
        {
            get => _status;
            set
            {
                _status = value;
                OnPropertyChanged();
            }
        }

        public uint DinersNum
        {
            get => _dinersNum;
            set
            {
                _dinersNum = value;
                OnPropertyChanged();
            }
        }

        public Stopwatch TotalStopwatch
        {
            get => _totalStopwatch;
            set
            {
                _totalStopwatch = value;
                OnPropertyChanged();
            }
        }

        public Stopwatch StatusStopwatch
        {
            get => _statusStopwatch;
            set
            {
                _statusStopwatch = value;
                OnPropertyChanged();
            }
        }
    }
}
